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
// parent_id является полем Node::id родительской ноды
void DirectoryManager::add(const Directory& directory, size_t parent_id) {
    size_t new_dir_id = dir_mg_->add(directory);

    //  Добавляемая директория наследует тип родительской
    const Node& parent_node = node_mg_->get(parent_id);
    
    Node new_node {
        0,
        parent_id,
        new_dir_id,
        parent_node.type
    };
    
    node_mg_->add(new_node);
}

void DirectoryManager::update(const Directory& directory) {}

void DirectoryManager::remove(size_t directory_id) {
    // TODO(uma_op): Вероятно стоит перенести процесс удаления в NodeManager

    const Directory& dir = dir_mg_->get(directory_id);
    const Node& dir_node = node_mg_->get(dir.node_id);

    std::queue<Node> subtree;
    subtree.push(dir_node);

    Node cur_node;

    while (!subtree.empty()) {
        cur_node = subtree.front();
        for (auto child_node : node_mg_->getChildren(cur_node.id))
            subtree.push(child_node);
        
        if (cur_node.type == NodeType::DIRECTORY)
            dir_mg_->remove(cur_node.resource_id);

        node_mg_->remove(cur_node.id);
        
        subtree.pop();
    }
}


std::vector<Event> DirectoryManager::getEvents(size_t directory_id) {
    return std::vector<Event>();
}

