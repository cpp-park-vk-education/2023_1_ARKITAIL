#include <queue>
#include <vector>

#include "NodeManager.hpp"
#include "Node.hpp"

const Node& NodeManager::get(size_t node_id) {
	return node_mg_->get(node_id);
}

void NodeManager::add(const Node& node) {
	node_mg_->add(node);
}

void NodeManager::update(const Node& node) {
	node_mg_->update(node);
}

void NodeManager::remove(size_t node_id) {
	const Node& node = node_mg_->get(node_id);

    std::queue<Node> subtree;
    subtree.push(node);

    Node cur_node;

    while (!subtree.empty()) {
        cur_node = subtree.front();

		if (cur_node.type & (NodeType::PRIVATE_DIRECTORY | NodeType::PUBLIC_DIRECTORY)) {
        	for (auto child_node : node_mg_->getChildren(cur_node.id))
            	subtree.push(child_node);

		}

        node_mg_->remove(cur_node.id);
		
		if (cur_node.type & (NodeType::PRIVATE_DIRECTORY | NodeType::PUBLIC_DIRECTORY))
            dir_mg_->remove(cur_node.resource_id);
		else if (cur_node.type & (NodeType::PRIVATE_CALENDAR | NodeType::PUBLIC_CALENDAR))
			cal_mg_->remove(cur_node.resource_id);
        
        subtree.pop();
    }

}

void NodeManager::move(size_t node_id, size_t destination_id) {
	const Node& mv_node = node_mg_->get(node_id); 
	Node mvd_node = mv_node;
	mvd_node.parent_id = destination_id;
}

void NodeManager::subscribe(size_t node_id) {
	const User& user = user_mg_->get();

	std::vector<Node> groups = node_mg_->getChildren(user.root_id);
	for (auto sub : groups) {
		if (sub.type & NodeType::SUBSCRIPTIONS_GROUP) {
			Node mount_node = {
				0,
				sub.id,
				node_id,
				NodeType::MOUNT
			};
			
			node_mg_->add(mount_node);
		}
	}
}

