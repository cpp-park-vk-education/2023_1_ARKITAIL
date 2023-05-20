#include <queue>
#include <vector>
#include <memory>

#include "DbManagers.hpp"
#include "IDbManagers.hpp"
#include "Managers.hpp"
#include "NodeManager.hpp"
#include "Node.hpp"

NodeManager::NodeManager(std::shared_ptr<IDbManagers> db) :
	db_(db) {}

const Node& NodeManager::get(size_t node_id) {
	return db_->node_dbm()->get(node_id);
}

size_t NodeManager::add(const Node& node) {
	return db_->node_dbm()->add(node);
}

void NodeManager::update(const Node& node) {
	db_->node_dbm()->update(node);
}

void NodeManager::remove(size_t node_id) {
	const Node& node = db_->node_dbm()->get(node_id);

	std::queue<Node> subtree;
	subtree.push(node);

	Node cur_node;

	while (!subtree.empty()) {
		cur_node = subtree.front();

		if (cur_node.type & (NodeType::PRIVATE_DIRECTORY | NodeType::PUBLIC_DIRECTORY))
			for (auto child_node : db_->node_dbm()->getChildren(cur_node.id))
				subtree.push(child_node);

		db_->node_dbm()->remove(cur_node.id);
		
		if (cur_node.type & (NodeType::PRIVATE_DIRECTORY | NodeType::PUBLIC_DIRECTORY))
			db_->directory_dbm()->remove(cur_node.resource_id);
		else if (cur_node.type & (NodeType::PRIVATE_CALENDAR | NodeType::PUBLIC_CALENDAR))
			db_->calendar_dbm()->remove(cur_node.resource_id);
        
		subtree.pop();
	}
}

void NodeManager::tag(const Tag& tag, size_t node_id) {
	// TODO(uma_op): IMPLEMENT ME
}

void NodeManager::move(size_t node_id, size_t destination_id) {
	const Node& mv_node = db_->node_dbm()->get(node_id); 
	Node mvd_node = mv_node;
	mvd_node.parent_id = destination_id;
}

void NodeManager::subscribe(size_t node_id) {
	const User& user = db_->user_dbm()->get();

	for (auto subg : db_->node_dbm()->getChildren(user.root_id())) {
		if (subg.type & NodeType::SUBSCRIPTIONS_GROUP) {
			Node mount_node = {
				0,
				subg.id,
				node_id,
				NodeType::MOUNT
			};
				
			db_->node_dbm()->add(mount_node);

			break;
		}
	}
}

void NodeManager::unsubscribe(size_t node_id) {
	const User& user = db_->user_dbm()->get();

	for (auto subg : db_->node_dbm()->getChildren(user.root_id()))
		if (subg.type & NodeType::SUBSCRIPTIONS_GROUP) {
			for (auto sub : db_->node_dbm()->getChildren(subg.id))
				if (sub.resource_id == node_id) {
					db_->node_dbm()->remove(sub.id);
					break;
				}

			break;
		}
}

std::vector<Node> NodeManager::getChildren(size_t node_id) {
	return db_->node_dbm()->getChildren(node_id);
}

