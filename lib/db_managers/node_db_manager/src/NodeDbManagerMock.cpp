#include <memory>

#include "DbMock.hpp"
#include "NodeDbManagerMock.hpp"
#include "Node.hpp"

NodeDbManagerMock::NodeDbManagerMock(std::shared_ptr<DbMock> db) :
	db_(db),
	aid_(db_->nodes.size()) {}

const Node& NodeDbManagerMock::get(size_t node_id) {
	for (auto e = db_->nodes.begin() + 1; e != db_->nodes.end(); e++)
		if (e->id == node_id)
			return *e;
	
	return db_->nodes[0];
}

size_t NodeDbManagerMock::add(const Node& node) {
	db_->nodes.emplace_back(
		aid_,
		node.parent_id,
		node.resource_id,
		node.type
	);

	return aid_++;
}

void NodeDbManagerMock::update(const Node& node) {
	for (auto e : db_->nodes)
		if (e.id == node.id)
			e = node;
}

void NodeDbManagerMock::remove(size_t node_id) {
	for (auto e = db_->nodes.begin() + 1; e != db_->nodes.end(); e++)
		if (e->id == node_id)
			db_->nodes.erase(e);
}

std::vector<Node> NodeDbManagerMock::getChildren(size_t node_id) {
	std::vector<Node> children;

	for (auto e : db_->nodes)
		if (e.parent_id == node_id)
			children.push_back(e);

	return children;
}

