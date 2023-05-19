#include "NodeDbManagerMock.hpp"
#include "Node.hpp"

NodeDbManagerMock::NodeDbManagerMock() :
	data_(),
	aid_() {
	
	data_.emplace_back(0, 0, 0, NodeType::ROOT);

	data_.emplace_back(1, 1, 1, NodeType::ROOT);
	data_.emplace_back(2, 2, 2, NodeType::ROOT);
	data_.emplace_back(3, 1, 3, NodeType::PRIVATE_GROUP);
	data_.emplace_back(4, 1, 4, NodeType::PUBLIC_GROUP);
	data_.emplace_back(5, 1, 5, NodeType::SUBSCRIPTIONS_GROUP);
	data_.emplace_back(6, 1, 6, NodeType::PROFILE_GROUP);
	data_.emplace_back(7, 3, 7, NodeType::PRIVATE_DIRECTORY);
	data_.emplace_back(8, 7, 1, NodeType::PRIVATE_CALENDAR);
	data_.emplace_back(9, 3, 2, NodeType::PRIVATE_CALENDAR);
	data_.emplace_back(10, 4, 8, NodeType::PUBLIC_DIRECTORY);
	data_.emplace_back(11, 10, 3, NodeType::PUBLIC_CALENDAR);
	data_.emplace_back(12, 4, 4, NodeType::PUBLIC_CALENDAR);
	data_.emplace_back(13, 5, 22, NodeType::MOUNT);
	data_.emplace_back(14, 6, 0, NodeType::PROFILE);
	data_.emplace_back(15, 2, 9, NodeType::PRIVATE_GROUP);
	data_.emplace_back(16, 2, 10, NodeType::PUBLIC_GROUP);
	data_.emplace_back(17, 2, 11, NodeType::SUBSCRIPTIONS_GROUP);
	data_.emplace_back(18, 2, 12, NodeType::PROFILE_GROUP);
	data_.emplace_back(19, 15, 13, NodeType::PRIVATE_DIRECTORY);
	data_.emplace_back(20, 19, 5, NodeType::PRIVATE_CALENDAR);
	data_.emplace_back(21, 15, 6, NodeType::PRIVATE_CALENDAR);
	data_.emplace_back(22, 16, 14, NodeType::PUBLIC_DIRECTORY);
	data_.emplace_back(23, 22, 7, NodeType::PUBLIC_CALENDAR);
	data_.emplace_back(24, 16, 8, NodeType::PUBLIC_CALENDAR);
	data_.emplace_back(25, 17, 10, NodeType::MOUNT);
	data_.emplace_back(26, 18, 0, NodeType::PROFILE);

	aid_ = data_.size();
}

const Node& NodeDbManagerMock::get(size_t node_id) {
	for (auto e = data_.begin() + 1; e != data_.end(); e++)
		if (e->id == node_id)
			return *e;
	
	return data_[0];
}

size_t NodeDbManagerMock::add(const Node& node) {
	data_.emplace_back(
		aid_,
		node.parent_id,
		node.resource_id,
		node.type
	);

	return aid_++;
}

void NodeDbManagerMock::update(const Node& node) {
	for (auto e : data_)
		if (e.id == node.id)
			e = node;
}

void NodeDbManagerMock::remove(size_t node_id) {
	for (auto e = data_.begin() + 1; e != data_.end(); e++)
		if (e->id == node_id)
			data_.erase(e);
}

std::vector<Node> NodeDbManagerMock::getChildren(size_t node_id) {
	std::vector<Node> children;

	for (auto e : data_)
		if (e.parent_id == node_id)
			children.push_back(e);

	return children;
}

