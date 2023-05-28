#include <memory>
#include <string>

#include <Wt/WLogger.h>

#include "DbManagers.hpp"
#include "DbMock.hpp"
#include "Node.hpp"
#include "NodeDbManagerMock.hpp"
#include "Tag.hpp"
#include "TagDbManagerMock.hpp"

NodeDbManagerMock::NodeDbManagerMock(std::shared_ptr<DbMock> db)
    : db_(db), aid_() {
  aid_ = (db_->nodes.size());
}

NodeSptr NodeDbManagerMock::get(int node_id) {
  Wt::log("NodeDbManagerMock::get: requested " + std::to_string(node_id));
  for (auto e = db_->nodes.begin() + 1; e != db_->nodes.end(); e++)
    if (e->id == node_id) {
      NodeSptr node = std::make_shared<Node>(*e);
      Wt::log("NodeDbManagerMock::get: found; is nullptr: " + std::to_string(node == nullptr));
      return node;
    }

  Wt::log("NodeDbManagerMock::get: not found");
  return std::make_shared<Node>(db_->nodes[0]);
}

int NodeDbManagerMock::add(NodeSptr node) {
  db_->nodes.emplace_back(
	aid_, 
	node->parent_id, 
	node->resource_id, 
	node->type
	);

  return aid_++;
}

void NodeDbManagerMock::update(NodeSptr node) {
  for (auto e : db_->nodes)
    if (e.id == node->id)
      e = *node;
}

void NodeDbManagerMock::remove(int node_id) {
  for (auto e = db_->nodes.begin() + 1; e != db_->nodes.end(); e++)
    if (e->id == node_id)
      db_->nodes.erase(e);
}

std::vector<Node> NodeDbManagerMock::getChildren(int node_id) {
  std::vector<Node> children;

  for (auto e : db_->nodes)
    if (e.parent_id == node_id && e.id != node_id)
      children.push_back(e);

  return children;
}

void NodeDbManagerMock::tag(int node_id, TagSptr tag) {
}

void NodeDbManagerMock::move(int node_id, int destination_id) {
}
