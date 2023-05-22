#include "nodeDbManager.hpp"

int NodeManager::Add(RetNode &ret) {
  RetTag t_ret;
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

void NodeManager::Remove(int id) {
  dbo::Transaction transaction(session_);

  dbo::ptr<Nodes> node = session_.find<Nodes>().where("id = ?").bind(id);
  if (!node) {
    return;
  }
  node.remove();
  transaction.commit();
}

void NodeManager::Update(RetNode &ret) {
  dbo::Transaction transaction(session_);

  dbo::ptr<Nodes> node =
      session_.find<Nodes>().where("id = ?").bind(ret.node_id);
  if (!node) {
    return;
  }
  node.modify()->parent =
      session_.find<Nodes>().where("id = ?").bind(ret.parent_id);
  node.modify()->resource_id = ret.resource_id;
  node.modify()->type = ret.type;

  transaction.commit();
}

RetNode NodeManager::Get(int id) {
  dbo::Transaction transaction(session_);

  RetNode ret;
  dbo::ptr<Nodes> node = session_.find<Nodes>().where("id = ?").bind(id);
  if (!node) {
    return ret;
  }
  ret.parent_id = node->parent.id();
  ret.type = node->type;
  ret.resource_id = node->resource_id;

  transaction.commit();

  return ret;
}

void NodeManager::Tag(int id, RetTag &rec) {
  dbo::Transaction transaction(session_);

  dbo::ptr<Tags> tag = session_.find<Tags>().where("id = ?").bind(rec.tag_id);
  std::cout << tag.get()->name << std::endl;
  dbo::ptr<Nodes> node = session_.find<Nodes>().where("id = ?").bind(id);
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

void NodeManager::Move(int id, const int destination_id) {
  dbo::Transaction transaction(session_);

  dbo::ptr<Nodes> node = session_.find<Nodes>().where("id = ?").bind(id);
  if (!node) {
    return;
  }
  node.modify()->parent =
      session_.find<Nodes>().where("id = ?").bind(destination_id);

  transaction.commit();
}

std::vector<RetNode> NodeManager::GetChildren(int id) {
  dbo::Transaction transaction(session_);
  RetNode ret;
  std::vector<RetNode> children;
  dbo::collection<dbo::ptr<Nodes>> node =
      session_.find<Nodes>().where("parent = ?").bind(id);
  for (const dbo::ptr<Nodes> &nod : node) {
    ret.parent_id = id;
    ret.resource_id = nod->resource_id;
    ret.type = nod->type;
    children.push_back(ret);
  }

  transaction.commit();
  return children;
}
