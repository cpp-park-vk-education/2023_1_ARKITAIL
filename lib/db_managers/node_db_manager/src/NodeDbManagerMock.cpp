#include "NodeDbManagerMock.hpp"
#include "Node.hpp"

NodeDbManagerMock::NodeDbManagerMock() :
	data_(),
	aid_(1){
	
	data_.emplace_back(0, 0, 0, NodeType::ROOT);
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

