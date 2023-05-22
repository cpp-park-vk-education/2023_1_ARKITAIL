#include <vector>
#include <queue>
#include <memory>

#include "DbManagers.hpp"
#include "Directory.hpp"
#include "DirectoryManager.hpp"
#include "Event.hpp"
#include "Managers.hpp"

DirectoryManager::DirectoryManager(std::shared_ptr<IDbManagers> db) :
    db_(db) {}

const Directory& DirectoryManager::get(int directory_id) {
    return db_->directory_dbm()->get(directory_id);
}

// Для добавления директория должна содежать следуюшие поля:
// Directory::owner_id
// Directory::name
// Directory::description
//
// Остальные поля не участвуют в добавлении опускаются 
//
// parent_id является полем Directory::id родительской директории
int DirectoryManager::add(const Directory& directory, int parent_id) {
    int new_dir_id = db_->directory_dbm()->add(directory);

    //  Добавляемая директория наследует тип родительской
    const Node& parent_node = db_->node_dbm()->get(db_->directory_dbm()->get(parent_id).node_id);
    
    Node new_node {
        0,
        parent_node.id,
        new_dir_id,
        parent_node.type
    };
    
    return db_->node_dbm()->add(new_node);
}

void DirectoryManager::update(const Directory& directory) {
    // TODO(uma_op): IMPLEMENT ME
}

void DirectoryManager::remove(int directory_id) {
    db_->node_dbm()->remove(db_->directory_dbm()->get(directory_id).node_id);
}

std::vector<Event> DirectoryManager::getEvents(int directory_id) {
    // TODO(uma_op): IMPLEMENT ME

    return std::vector<Event>();
}

