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
  db_node_unique->parent_id =
      session_.find<db::Node>().where("id = ?").bind(node->parent_id);

  transaction.commit();

  return id_;
}

void NodeDbManager::remove(int node_id) {
  Wt::Dbo::Transaction transaction(session_);

  db::NodePtr db_node = session_.find<db::Node>().where("id = ?").bind(node_id);

  if (!db_node) {
    return;
  }

  db_node.remove();
  transaction.commit();
}

void NodeDbManager::update(NodeSptr node) {
  Wt::Dbo::Transaction transaction(session_);

  db::NodePtr db_node =
      session_.find<db::Node>().where("id = ?").bind(node->id);

  if (!db_node) {
    return;
  }

  db_node.modify()->parent_id =
      session_.find<db::Node>().where("id = ?").bind(node->parent_id);
  db_node.modify()->resource_id = node->resource_id;
  db_node.modify()->type = node->type;

  transaction.commit();
}

NodeSptr NodeDbManager::get(int node_id) {
  db::NodePtr db_node = session_.find<db::Node>().where("id = ?").bind(node_id);

  if (!db_node) {
    return nullptr;
  }

  NodeSptr node = std::make_shared<Node>();
  node->parent_id = db_node->parent_id.id();
  node->type = db_node->type;
  node->resource_id = db_node->resource_id;

  return node;
}

void NodeDbManager::tag(int node_id, TagSptr tag) {
  Wt::Dbo::Transaction transaction(session_);

  db::TagPtr db_tag = session_.find<db::Tag>().where("id = ?").bind(tag->id);

  db::NodePtr db_node = session_.find<db::Node>().where("id = ?").bind(node_id);

  if (!db_node) {
    return;
  }

  if (!db_tag) {
    // affeeal->Antihoman: здесь, типо, добавление работает без session.flush?
    // Не уверен, но лучше добавлю, так точно сраюотает
    db_tag = session_.add(std::make_unique<db::Tag>());
    session_.flush();
    db_tag.modify()->name = tag->name;
  }

  db_node.modify()->tags.insert(db_tag);

  transaction.commit();
}

void NodeDbManager::move(int node_id, int destination_id) {
  Wt::Dbo::Transaction transaction(session_);

  db::NodePtr db_node = session_.find<db::Node>().where("id = ?").bind(node_id);

  if (!db_node) {
    return;
  }

  db_node.modify()->parent_id =
      session_.find<db::Node>().where("id = ?").bind(destination_id);

  transaction.commit();
}

std::vector<Node> NodeDbManager::getChildren(int node_id) {
  std::vector<Node> children;

  // affeeal->Antihoman: переименовать parent в parent_id
  Wt::Dbo::collection<db::NodePtr> db_nodes =
      session_.find<db::Node>().where("parent = ?").bind(node_id);

  for (const db::NodePtr &db_node : db_nodes) {
    Node node;
    node.id = node_id;
    node.parent_id = node_id;
    node.resource_id = db_node->resource_id;
    node.type = db_node->type;
    children.push_back(node);
  }

  return children;
}

void NodeDbManager::profile(int node_id, ProfileSptr profile) {
  Wt::Dbo::Transaction transaction(session_);

  db::ProfilePtr db_profile = session_.find<db::Profile>().where("id = ?").bind(profile->id);

  db::NodePtr db_node = session_.find<db::Node>().where("id = ?").bind(node_id);

  if (!db_node) {
    return;
  }

  if (!db_profile) {
    db_profile = session_.add(std::make_unique<db::Profile>());
    session_.flush();
    db_profile.modify()->node_id = session_.find<db::Node>().where("id = ?").bind(profile->node_id);
    db_profile.modify()->owner_id = session_.find<db::User>().where("id = ?").bind(profile->owner_id);
  }

  db_node.modify()->profiles.insert(db_profile);

  transaction.commit();
}