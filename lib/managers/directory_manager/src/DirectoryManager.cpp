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

<<<<<<< HEAD
// Проверки доступа
Directory DirectoryManager::get(size_t directory_id) {
    User user = db_->user_dbm()->get();
    Directory directory = db_->directory_dbm()->get(directory_id);
    Node node = db_->node_dbm()->get(directory.node_id);

    if (!(user.id == directory.owner_id || node.type & PUBLIC_DIRECTORY))
        return Directory();

    return directory;
=======
const Directory& DirectoryManager::get(int directory_id) {
    return db_->directory_dbm()->get(directory_id);
>>>>>>> origin/impl-lukyanov
}

// Для добавления директория должна содежать следуюшие поля:
// Directory::owner_id
// Directory::name
// Directory::description
//
// Остальные поля не участвуют в добавлении (опускаются) 
//
// parent_id является полем Directory::id родительской директории
<<<<<<< HEAD
size_t DirectoryManager::add(const Directory& directory, size_t parent_id) {
    User user = db_->user_dbm()->get();
    Directory parent_directory = get(parent_id);
=======
int DirectoryManager::add(const Directory& directory, int parent_id) {
    int new_dir_id = db_->directory_dbm()->add(directory);
>>>>>>> origin/impl-lukyanov

    if (!parent_directory.id || user.id != parent_directory.owner_id)
        return 0;

    auto node_mgr = SessionScopeMap::instance().get()->managers()->node_manager();

    Node parent_node = node_mgr->get(get(parent_id).node_id);
    Node new_node = {0, parent_node.id, 0, parent_node.type};

    size_t new_node_id = node_mgr->add(new_node);

    if (!new_node_id)
        return 0;

    Directory new_directory = directory;
    new_directory.node_id = new_node_id;
    
    return db_->directory_dbm()->add(directory);
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

<<<<<<< HEAD
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
=======
void DirectoryManager::remove(int directory_id) {
    db_->node_dbm()->remove(db_->directory_dbm()->get(directory_id).node_id);
}

std::vector<Event> DirectoryManager::getEvents(int directory_id) {
    // TODO(uma_op): IMPLEMENT ME
>>>>>>> origin/impl-lukyanov

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

