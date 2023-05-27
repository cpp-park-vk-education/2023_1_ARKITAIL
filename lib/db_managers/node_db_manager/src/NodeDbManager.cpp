#include "NodeDbManager.hpp"

#include "DbModels.hpp"
#include "Node.hpp"

int NodeDbManager::add(NodeSptr node) {
  Wt::Dbo::Transaction transaction(session_);

  std::unique_ptr<db::Node> db_node_unique = std::make_unique<db::Node>();
  db_node_unique->resource_id = node->resource_id;
  db_node_unique->type = node->type;

  db::NodePtr db_node = session_.add(std::move(db_node_unique));
  id_ = db_node.id();

  session_.flush();

  // родителя устанавливаем только здесь, так как изначально могли его не найти
  db_node_unique->parent
      = session_.find<db::Node>().where("id = ?").bind(node->parent_id);

  transaction.commit();
  
  return id_;
}

void NodeDbManager::remove(int node_id) {
  Wt::Dbo::Transaction transaction(session_);

  db::NodePtr db_node
      = session_.find<db::Node>().where("id = ?").bind(node_id);

  if (!db_node) {
    return;
  }

  db_node.remove();
  transaction.commit();
}

void NodeDbManager::update(NodeSptr node) {
  Wt::Dbo::Transaction transaction(session_);

  db::NodePtr db_node
      = session_.find<db::Node>().where("id = ?").bind(node->id);

  if (!db_node) {
    return;
  }

  db_node.modify()->parent =
      session_.find<db::Node>().where("id = ?").bind(node->parent_id);
  db_node.modify()->resource_id = node->resource_id;
  db_node.modify()->type = node->type;

  transaction.commit();
}

NodeSptr NodeDbManager::get(int node_id) {
  Wt::Dbo::Transaction transaction(session_);

  db::NodePtr db_node
      = session_.find<db::Node>().where("id = ?").bind(node_id);

  if (!db_node) {
    return nullptr;
  }

  Node node;
  node.parent_id = db_node->parent.id();
  node.type = db_node->type;
  node.resource_id = db_node->resource_id;
  node.id = node_id;

  transaction.commit();

  return std::make_shared<Node>(std::move(node));
}

void NodeDbManager::tag(int node_id, TagSptr tag) {
  Wt::Dbo::Transaction transaction(session_);

  db::TagPtr db_tag
      = session_.find<db::Tag>().where("id = ?").bind(tag->id);

  db::NodePtr db_node
      = session_.find<db::Node>().where("id = ?").bind(node_id);

  if (!db_node) {
    return;
  }

  if (!db_tag) {
    // affeeal->Antihoman: здесь, типо, добавление работает без session.flush?
    db_tag = session_.add(std::make_unique<db::Tag>());
    db_tag.modify()->name = tag->name;
  }

  db_node.modify()->tags.insert(db_tag);

  transaction.commit();
}

void NodeDbManager::move(int node_id, int destination_id) {
  Wt::Dbo::Transaction transaction(session_);

  db::NodePtr db_node
      = session_.find<db::Node>().where("id = ?").bind(node_id);

  if (!db_node) {
    return;
  }

  db_node.modify()->parent
      = session_.find<db::Node>().where("id = ?").bind(destination_id);

  transaction.commit();
}

std::vector<Node> NodeDbManager::getChildren(int node_id) {
  std::vector<Node> children;

  // affeeal->Antihoman: переименовать parent в parent_id
  Wt::Dbo::collection<db::NodePtr> db_nodes =
      session_.find<db::Node>().where("parent = ?").bind(node_id);

  for (const db::NodePtr& db_node : db_nodes) {
    Node node;
    node.parent_id = node_id;
    node.resource_id = db_node->resource_id;
    node.type = db_node->type;
    children.push_back(node);
  }

  return children;
}
