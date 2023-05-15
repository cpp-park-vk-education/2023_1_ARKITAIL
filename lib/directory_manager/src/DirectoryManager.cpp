#include <vector>
#include <queue>

#include "Directory.hpp"
#include "DirectoryManager.hpp"
#include "Event.hpp"
#include "Managers.hpp"

const Directory& DirectoryManager::get(size_t directory_id) {
    return manager_->get(directory_id);
}

// Для добавления директория должна содежать следуюшие поля:
// Directory::owner_id
// Directory::name
// Directory::description
//
// Остальные поля не участвуют в добавлении опускаются 
//
// parent_id является полем Directory::id родительской директории
size_t DirectoryManager::add(const Directory& directory, size_t parent_id) {
    size_t new_dir_id = manager_->add(directory);

    //  Добавляемая директория наследует тип родительской
    const Node& parent_node = Managers::instance().node_manager->get(manager_->get(parent_id).node_id);
    
    Node new_node {
        0,
        parent_node.id,
        new_dir_id,
        parent_node.type
    };
    
    return Managers::instance().node_manager->add(new_node);
}

void DirectoryManager::update(const Directory& directory) {
    // TODO(uma_op): IMPLEMENT ME
}

void DirectoryManager::remove(size_t directory_id) {
    Managers::instance().node_manager->remove(manager_->get(directory_id).node_id);
}

std::vector<Event> DirectoryManager::getEvents(size_t directory_id) {
    // TODO(uma_op): IMPLEMENT ME

    return std::vector<Event>();
}

