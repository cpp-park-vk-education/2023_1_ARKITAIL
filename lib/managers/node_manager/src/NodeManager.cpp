#include <queue>
#include <vector>

#include "Managers.hpp"
#include "NodeManager.hpp"
#include "Node.hpp"

const Node& NodeManager::get(size_t node_id) {
	return manager_->get(node_id);
}

size_t NodeManager::add(const Node& node) {
	return manager_->add(node);
}

void NodeManager::update(const Node& node) {
	manager_->update(node);
}

void NodeManager::remove(size_t node_id) {
	const Node& node = manager_->get(node_id);

	std::queue<Node> subtree;
	subtree.push(node);

	Node cur_node;

	while (!subtree.empty()) {
		cur_node = subtree.front();

		if (cur_node.type & (NodeType::PRIVATE_DIRECTORY | NodeType::PUBLIC_DIRECTORY))
			for (auto child_node : manager_->getChildren(cur_node.id))
				subtree.push(child_node);

		manager_->remove(cur_node.id);
		
		if (cur_node.type & (NodeType::PRIVATE_DIRECTORY | NodeType::PUBLIC_DIRECTORY))
			Managers::instance().directory_manager->remove(cur_node.resource_id);
		else if (cur_node.type & (NodeType::PRIVATE_CALENDAR | NodeType::PUBLIC_CALENDAR))
			Managers::instance().calendar_manager->remove(cur_node.resource_id);
        
		subtree.pop();
	}
}

void NodeManager::tag(const Tag& tag, size_t node_id) {
	// TODO(uma_op): IMPLEMENT ME
}

void NodeManager::move(size_t node_id, size_t destination_id) {
	const Node& mv_node = manager_->get(node_id); 
	Node mvd_node = mv_node;
	mvd_node.parent_id = destination_id;
}

void NodeManager::subscribe(size_t node_id) {
	const User& user = Managers::instance().user_manager->get();

	for (auto subg : manager_->getChildren(user.root_id)) {
		if (subg.type & NodeType::SUBSCRIPTIONS_GROUP) {
			Node mount_node = {
				0,
				subg.id,
				node_id,
				NodeType::MOUNT
			};
				
			manager_->add(mount_node);

			break;
		}
	}
}

void NodeManager::unsubscribe(size_t node_id) {
	const User& user = Managers::instance().user_manager->get();

	for (auto subg : manager_->getChildren(user.root_id))
		if (subg.type & NodeType::SUBSCRIPTIONS_GROUP) {
			for (auto sub : manager_->getChildren(subg.id))
				if (sub.resource_id == node_id) {
					manager_->remove(sub.id);
					break;
				}

			break;
		}
}

std::vector<Node> NodeManager::getChildren(size_t node_id) {
	return manager_->getChildren(node_id);
}

