#include <vector>
#include <queue>

#include "Directory.hpp"
#include "DirectoryManager.hpp"
#include "Event.hpp"

const Directory& DirectoryManager::get(size_t directory_id) {
    return dir_mg_->get(directory_id);
}

// Для добавления директория должна содежать следуюшие поля:
// Directory::owner_id
// Directory::name
// Directory::description
//
// Остальные поля не участвуют в добавлении опускаются 
//
// parent_id является полем Directory::id родительской директории
void DirectoryManager::add(const Directory& directory, size_t parent_id) {
    size_t new_dir_id = dir_mg_->add(directory);

    //  Добавляемая директория наследует тип родительской
    const Node& parent_node = node_mg_->get(dir_mg_->get(parent_id).node_id);
    
    Node new_node {
        0,
        parent_node.id,
        new_dir_id,
        parent_node.type
    };
    
    node_mg_->add(new_node);
}

void DirectoryManager::update(const Directory& directory) {}

void DirectoryManager::remove(size_t directory_id) {
    node_mg_->remove(dir_mg_->get(directory_id).node_id);
}

std::vector<Event> DirectoryManager::getEvents(size_t directory_id) {
    return std::vector<Event>();
}

