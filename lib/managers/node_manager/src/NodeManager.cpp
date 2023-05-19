#include <queue>
#include <vector>

#include "DbManagers.hpp"
#include "Managers.hpp"
#include "NodeManager.hpp"
#include "Node.hpp"

const Node& NodeManager::get(size_t node_id) {
	return DbManagers::instance().node_dbm->get(node_id);
}

size_t NodeManager::add(const Node& node) {
	return DbManagers::instance().node_dbm->add(node);
}

void NodeManager::update(const Node& node) {
	DbManagers::instance().node_dbm->update(node);
}

void NodeManager::remove(size_t node_id) {
	const Node& node = DbManagers::instance().node_dbm->get(node_id);

	std::queue<Node> subtree;
	subtree.push(node);

	Node cur_node;

	while (!subtree.empty()) {
		cur_node = subtree.front();

		if (cur_node.type & (NodeType::PRIVATE_DIRECTORY | NodeType::PUBLIC_DIRECTORY))
			for (auto child_node : DbManagers::instance().node_dbm->getChildren(cur_node.id))
				subtree.push(child_node);

		DbManagers::instance().node_dbm->remove(cur_node.id);
		
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
	const Node& mv_node = DbManagers::instance().node_dbm->get(node_id); 
	Node mvd_node = mv_node;
	mvd_node.parent_id = destination_id;
}

void NodeManager::subscribe(size_t node_id) {
	const User& user = Managers::instance().user_manager->get();

	for (auto subg : DbManagers::instance().node_dbm->getChildren(user.root_id)) {
		if (subg.type & NodeType::SUBSCRIPTIONS_GROUP) {
			Node mount_node = {
				0,
				subg.id,
				node_id,
				NodeType::MOUNT
			};
				
			DbManagers::instance().node_dbm->add(mount_node);

			break;
		}
	}
}

void NodeManager::unsubscribe(size_t node_id) {
	const User& user = Managers::instance().user_manager->get();

	for (auto subg : DbManagers::instance().node_dbm->getChildren(user.root_id))
		if (subg.type & NodeType::SUBSCRIPTIONS_GROUP) {
			for (auto sub : DbManagers::instance().node_dbm->getChildren(subg.id))
				if (sub.resource_id == node_id) {
					DbManagers::instance().node_dbm->remove(sub.id);
					break;
				}

			break;
		}
}

std::vector<Node> NodeManager::getChildren(size_t node_id) {
	return DbManagers::instance().node_dbm->getChildren(node_id);
}

