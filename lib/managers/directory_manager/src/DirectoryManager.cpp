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

DirectoryManager::DirectoryManager(std::shared_ptr<IDbManagers> db) :
    db_(db) {}

// Проверки доступа
Directory DirectoryManager::get(size_t directory_id) {
    User user = db_->user_dbm()->get();
    Directory directory = db_->directory_dbm()->get(directory_id);
    Node node = db_->node_dbm()->get(directory.node_id);

    if (!(user.id == directory.owner_id || node.type & PUBLIC_DIRECTORY))
        return Directory();

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
size_t DirectoryManager::add(const Directory& directory, size_t directory_id) {
    User user = db_->user_dbm()->get();
    Directory parent_directory = get(directory_id);

    if (!parent_directory.id || user.id != parent_directory.owner_id)
        return 0;

    auto node_mgr = SessionScopeMap::instance().get()->managers()->node_manager();

    Node parent_node = node_mgr->get(get(directory_id).node_id);
    Node new_node = {0, parent_node.id, 0, parent_node.type};

    new_node.id = node_mgr->add(new_node);

    if (!new_node.id)
        return 0;

    Directory new_directory = directory;
    new_directory.node_id = new_node.id;

    new_directory.id = db_->directory_dbm()->add(new_directory);
    new_node.resource_id = new_directory.id;
    db_->node_dbm()->update(new_node);
    
    return new_directry->id;
}

// Сменить можно только название и описание
void DirectoryManager::update(const Directory& directory) {
    User user = db_->user_dbm()->get();
    Directory prev_directory = get(directory.id);

    if (!prev_directory.id ||
        user.id != prev_directory.owner_id ||
        prev_directory.node_id != directory.node_id ||
        prev_directory.owner_id != directory.owner_id)
        return;

    db_->directory_dbm()->update(directory);   
}

void DirectoryManager::remove(size_t directory_id) {
    User user = db_->user_dbm()->get();
    Directory directory = get(directory_id);

    if (!directory.id ||
        user.id != directory.owner_id)
        return;

    // Менеджер нод удаляет также и связанные ресурсы
    auto node_mgr = SessionScopeMap::instance().get()->managers()->node_manager();
    node_mgr->remove(directory.node_id);
}

std::vector<EventSptr> DirectoryManager::getEvents(size_t directory_id) {
    Directory directory = db_->directory_dbm()->get(directory_id);

    if (!directory.id)
        return std::vector<EventSptr>();

    auto node_mgr = SessionScopeMap::instance().get()->managers()->node_manager();
    Node node = node_mgr->get(directory.node_id);

    if (!node.id)
        return std::vector<EventSptr>();

    auto calendar_mgr = SessionScopeMap::instance().get()->managers()->calendar_manager();

    std::vector<EventSptr> events;
    std::queue<Node> q;

    q.push(node);

    while (!q.empty()) {
        if (q.front().type & (PUBLIC_DIRECTORY | PRIVATE_DIRECTORY))
            for (auto c : node_mgr->getChildren(q.front().id))
                q.push(c);
        else if (q.front().type & CALENDAR)
            for (auto e : calendar_mgr->getEvents(q.front().resource_id))
                events.push_back(e);


        q.pop();
    }

    return events;
}

