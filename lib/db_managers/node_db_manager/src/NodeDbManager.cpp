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

void NodeDbManager::tag(int node_id, const Tag &rec) {
  dbo::Transaction transaction(session_);

  dbo::ptr<Tags> tag = session_.find<Tags>().where("id = ?").bind(rec.id);
  std::cout << tag.get()->name << std::endl;
  dbo::ptr<Nodes> node = session_.find<Nodes>().where("id = ?").bind(node_id);
  std::cout << node << std::endl;

  if (!node) {
    return;
  }
  if (!tag) {
    std::cout << "!" << std::endl;
    tag = session_.add(std::unique_ptr<Tags>{new Tags()});
    tag.modify()->name = rec.name;
  }

  node.modify()->tag.insert(tag);

  transaction.commit();
}

void NodeDbManager::move(int node_id, int destination_id) {
  dbo::Transaction transaction(session_);

  dbo::ptr<Nodes> node = session_.find<Nodes>().where("id = ?").bind(node_id);
  if (!node) {
    return;
  }
  node.modify()->parent =
      session_.find<Nodes>().where("id = ?").bind(destination_id);

  transaction.commit();
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
