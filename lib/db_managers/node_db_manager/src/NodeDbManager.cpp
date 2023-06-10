#include "NodeDbManager.hpp"

#include <string>

#include <Wt/WLogger.h>
#include <Wt/Dbo/Transaction.h>

#include "DbModels.hpp"
#include "Node.hpp"
#include "Session.hpp"
#include "Tag.hpp"

NodeDbManager::NodeDbManager(Session& session)
    : session_(session) {
}

int NodeDbManager::add(NodeSptr node) {
  Wt::Dbo::Transaction transaction(session_);

  // собираем всё необходимое для создания ноды
  db::NodePtr db_parent
      = session_.find<db::Node>().where("id = ?").bind(node->parent_id);

  if (!db_parent) {
    Wt::log("NodeDbManger::add: not found node's parent with id = "
        + std::to_string(node->parent_id));
  }
  
  db::UserPtr db_owner
      = session_.find<db::User>().where("id = ?").bind(node->owner_id);

  if (!db_owner) {
    Wt::log("NodeDbManger::add: not found node's owner with id = "
        + std::to_string(node->owner_id));
  }

  // создаём ноду
  db::NodePtr db_node = session_.add(std::make_unique<db::Node>());
  
  // непосредственно сохраняем для получения id
  session_.flush();
  int id = static_cast<int>(db_node.id());

  // устанавливаем поля
  db_node.modify()->resource_id = node->resource_id;
  db_node.modify()->owner = db_owner;
  db_node.modify()->parent = db_parent;
  db_node.modify()->type = node->type;

  transaction.commit();
  
  return id;
}

void NodeDbManager::remove(int node_id) {
  Wt::Dbo::Transaction transaction(session_);

  db::NodePtr db_node
      = session_.find<db::Node>().where("id = ?").bind(node_id);

  if (!db_node) {
    Wt::log("NodeDbManger::remove: not found node with id = "
        + std::to_string(node_id));
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
    Wt::log("NodeDbManger::update: not found node with id = "
        + std::to_string(node->id));
    return;
  }

  db::NodePtr db_parent
      = session_.find<db::Node>().where("id = ?").bind(node->parent_id);
  
  if (!db_parent) {
    Wt::log("NodeDbManger::update: not found node's parent with id = "
        + std::to_string(node->parent_id));
    return;
  }

  db::UserPtr db_owner
      = session_.find<db::User>().where("id = ?").bind(node->owner_id);
  
  if (!db_owner) {
    Wt::log("NodeDbManger::update: not found node's owner with id = "
        + std::to_string(node->parent_id));
    return;
  }

  db_node.modify()->resource_id = node->resource_id;
  db_node.modify()->parent = db_parent;
  db_node.modify()->owner = db_owner;
  db_node.modify()->type = node->type;

  transaction.commit();
}

NodeSptr NodeDbManager::get(int node_id) {
  Wt::Dbo::Transaction transaction(session_);

  db::NodePtr db_node
      = session_.find<db::Node>().where("id = ?").bind(node_id);

  if (!db_node) {
    Wt::log("NodeDbManger::get: not found node with id = "
        + std::to_string(node_id));
    return std::make_shared<Node>();
  }

  Node node {
    static_cast<int>(db_node.id()),
    static_cast<int>(db_node->parent.id()),
    db_node->resource_id,
    static_cast<int>(db_node->owner.id()),
    db_node->type
  };

  transaction.commit();

  return std::make_shared<Node>(std::move(node));
}

void NodeDbManager::tag(int node_id, int tag_id) {
    Wt::Dbo::Transaction transaction(session_);

    db::TagPtr db_tag = session_.find<db::Tag>().where("id = ?").bind(tag_id);

    db::NodePtr db_node
      = session_.find<db::Node>().where("id = ?").bind(node_id);

    if (!db_node) {
        Wt::log("NodeDbManger::tag: not found node with id = " + std::to_string(node_id));
        return;
    }

    if (!db_node) {
        Wt::log("NodeDbManger::tag: not found tag with id = " + std::to_string(tag_id));
        return;
    }


  // if (!db_tag) {
  //   Wt::log("NodeDbManger::tag: not found tag with id = "
  //       + std::to_string(tag->id) + "; creating new one");
  //   
  //   db_tag = session_.add(std::make_unique<db::Tag>());
  //   db_tag.modify()->name = tag->name;
  // }

    db_node.modify()->tags.insert(db_tag);

    transaction.commit();
}

std::vector<Node> NodeDbManager::getChildren(int node_id) {
  Wt::Dbo::Transaction transaction(session_);
  
  Wt::Dbo::collection<db::NodePtr> db_children
      = session_.find<db::Node>().where("parent_id = ?").bind(node_id);

  if (db_children.empty()) {
    Wt::log("NodeDbManager::getChildren: not found children of node with id = "
        + std::to_string(node_id));
    return std::vector<Node>();
  }
  
  std::vector<Node> children;
  for (const db::NodePtr& db_node : db_children) {
    children.push_back(Node {
        static_cast<int>(db_node.id()),
        static_cast<int>(db_node->parent.id()),
        db_node->resource_id,
        static_cast<int>(db_node->owner.id()),
        db_node->type,
    });
  }

  transaction.commit();

  return children;
}

std::vector<TagSptr> NodeDbManager::tagByNode(int node_id) {
    return std::vector<TagSptr>();
}

