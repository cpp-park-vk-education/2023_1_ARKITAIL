#include "NodeDbManager.hpp"

int NodeDbManager::add(const Node &ret) {
  Tag t_ret;
  dbo::Transaction transaction(session_);

  std::unique_ptr<Nodes> node{new Nodes()};
  node->parent = session_.find<Nodes>().where("id = ?").bind(ret.parent_id);
  node->resource_id = ret.resource_id;
  node->type = ret.type;

  dbo::ptr<Nodes> nodePtr = session_.add(std::move(node));

  session_.flush();
  transaction.commit();
  id_ = nodePtr.id();

  dbo::Transaction transac(session_);

  dbo::ptr<Nodes> nodee = session_.find<Nodes>().where("id = ?").bind(id_);

  nodee.modify()->parent =
      session_.find<Nodes>().where("id = ?").bind(ret.parent_id);
  transac.commit();

  return id_;
}

void NodeDbManager::remove(int node_id) {
  dbo::Transaction transaction(session_);

  dbo::ptr<Nodes> node = session_.find<Nodes>().where("id = ?").bind(node_id);
  if (!node) {
    return;
  }
  node.remove();
  transaction.commit();
}

void NodeDbManager::update(const Node &ret) {
  dbo::Transaction transaction(session_);

  dbo::ptr<Nodes> node =
      session_.find<Nodes>().where("id = ?").bind(ret.id);
  if (!node) {
    return;
  }
  node.modify()->parent =
      session_.find<Nodes>().where("id = ?").bind(ret.parent_id);
  node.modify()->resource_id = ret.resource_id;
  node.modify()->type = ret.type;

  transaction.commit();
}

const Node& NodeDbManager::get(int node_id) {
  dbo::Transaction transaction(session_);

  Node ret;
  dbo::ptr<Nodes> node = session_.find<Nodes>().where("id = ?").bind(node_id);
  if (!node) {
    return ret;
  }
  ret.parent_id = node->parent.id();
  ret.type = node->type;
  ret.resource_id = node->resource_id;

  transaction.commit();

  return ret;
}

std::vector<Node> NodeDbManager::getChildren(int node_id) {
  dbo::Transaction transaction(session_);
  Node ret;
  std::vector<Node> children;
  dbo::collection<dbo::ptr<Nodes>> node =
      session_.find<Nodes>().where("parent = ?").bind(node_id);
  for (const dbo::ptr<Nodes> &nod : node) {
    ret.parent_id = node_id;
    ret.resource_id = nod->resource_id;
    ret.type = nod->type;
    children.push_back(ret);
  }

  transaction.commit();
  return children;
}
