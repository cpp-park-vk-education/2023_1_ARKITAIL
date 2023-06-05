#include <Wt/WLogger.h>
#include <vector>
#include <queue>
#include <memory>

#include "DbManagers.hpp"
#include "Directory.hpp"
#include "DirectoryManager.hpp"
#include "Event.hpp"
#include "Managers.hpp"
#include "Node.hpp"
#include "SessionScopeMap.hpp"
#include "User.hpp"

DirectoryManager::DirectoryManager(std::shared_ptr<IDbManagers> db) :
    db_(db) {}

// Проверки доступа
DirectorySptr DirectoryManager::get(int directory_id) {
    UserSptr user = db_->user_dbm()->get();
    DirectorySptr directory = db_->directory_dbm()->get(directory_id);
    NodeSptr node = db_->node_dbm()->get(directory->node_id);

    // affeeal: здесь какой-то баг или кто-то не проверят возвращаемое значение
    // на nullptr, поэтому пока исправил на вовзрат пустого DirectorySptr.
    if (!(user->id == directory->owner_id || node->type & PUBLIC_DIRECTORY))
      return std::make_shared<Directory>();

    return directory;
}

// Для добавления директория должна содежать следуюшие поля:
// Directory::owner_id
// Directory::name
// Directory::description
//
// Остальные поля не участвуют в добавлении (опускаются) 
//
// directory_id является полем Directory::id родительской директории
int DirectoryManager::add(DirectorySptr directory, int directory_id) {
    auto directory_mgr = SessionScopeMap::instance().get()->managers()->directory_manager();

    UserSptr user = db_->user_dbm()->get();
    DirectorySptr parent_directory = directory_mgr->get(directory_id);

    if (!parent_directory->id || user->id != parent_directory->owner_id)
        return 0;

    auto node_mgr = SessionScopeMap::instance().get()->managers()->node_manager();

    NodeSptr parent_node = node_mgr->get(directory_mgr->get(directory_id)->node_id);
    NodeSptr new_node = std::make_shared<Node>(
        0, parent_node->id, 0, parent_node->owner_id,
        (parent_node->type & PUBLIC ? PUBLIC_DIRECTORY : PRIVATE_DIRECTORY));

    new_node->id = node_mgr->add(new_node);

    if (!new_node->id)
        return 0;

    DirectorySptr new_directory = directory;
    new_directory->node_id = new_node->id;

    new_directory->id = db_->directory_dbm()->add(new_directory);
    new_node->resource_id = new_directory->id;
    db_->node_dbm()->update(new_node);
    
    return new_directory->id;
}

// Сменить можно только название и описание
void DirectoryManager::update(DirectorySptr directory) {
    UserSptr user = db_->user_dbm()->get();
    DirectorySptr prev_directory = get(directory->id);

    if (!prev_directory->id ||
        user->id != prev_directory->owner_id ||
        prev_directory->node_id != directory->node_id ||
        prev_directory->owner_id != directory->owner_id)
        return;

    db_->directory_dbm()->update(directory);   
}

void DirectoryManager::remove(int directory_id) {
    UserSptr user = db_->user_dbm()->get();
    DirectorySptr directory = get(directory_id);

    if (!directory->id || user->id != directory->owner_id)
        return;

    // Менеджер нод удаляет также и связанные ресурсы
    auto node_mgr = SessionScopeMap::instance().get()->managers()->node_manager();
    node_mgr->remove(directory->node_id);
}

std::vector<Event> DirectoryManager::getEvents(int directory_id) {
    DirectorySptr directory = db_->directory_dbm()->get(directory_id);

    if (!directory->id)
        return std::vector<Event>();

    auto node_mgr = SessionScopeMap::instance().get()->managers()->node_manager();
    NodeSptr node = node_mgr->get(directory->node_id);

    if (!node->id)
        return std::vector<Event>();

    auto calendar_mgr = SessionScopeMap::instance().get()->managers()->calendar_manager();

    std::vector<Event> events;
    std::queue<NodeSptr> q;

    q.push(node);

    while (!q.empty()) {
        if (q.front()->type & (PUBLIC_DIRECTORY | PRIVATE_DIRECTORY))
            for (auto c : node_mgr->getChildren(q.front()->id))
                q.push(std::make_shared<Node>(c));
        else if (q.front()->type & CALENDAR)
            for (auto e : calendar_mgr->getEvents(q.front()->resource_id))
                events.push_back(e);

        q.pop();
    }

    return events;
}

