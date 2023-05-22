#include "nodeDbManager.hpp"

int NodeManager::Add(RetNode &ret) {
  RetTag t_ret;
  dbo::Transaction transaction(session_);

  std::unique_ptr<Nodes> node{new Nodes()};
  node->parent = session_.find<Nodes>().where("id = ?").bind(ret.parent_id);
  node->resource_id = ret.resource_id;
  node->type = ret.type;

  dbo::ptr<Nodes> nodePtr = session_.add(std::move(node));
  nodePtr = session_.find<Nodes>().where("node_id = ?").bind(ret.node_id);

  session_.flush();
  transaction.commit();
  id_ = nodePtr.id();
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
      session_.find<Nodes>().where("resource_id = ?").bind(ret.resource_id);
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

  std::vector<int> tagv;
  RetNode ret;
  dbo::ptr<Nodes> node = session_.find<Nodes>().where("id = ?").bind(id);
  if (!node) {
    return ret;
  }
  ret.parent_id = node->parent.id();
  ret.type = node->type;
  ret.resource_id = node->resource_id;
  for (int i = 0; i < node->tag.size(); ++i) {
    dbo::ptr<Tags> id = session_.find<Tags>().where("node_id = ?").bind(id);
    tagv.push_back(id.id());
  }
  ret.tag_id = tagv;

  transaction.commit();

  return ret;
}

void NodeManager::Tag(int id, RetTag &rec) {
  dbo::Transaction transaction(session_);

  dbo::ptr<Tags> tag = session_.find<Tags>().where("name = ?").bind(rec.name);
  dbo::ptr<Nodes> node = session_.find<Nodes>().where("id = ?").bind(id);
  if (!node) {
    return;
  }
  if (!tag) {
    tag = session_.add(std::unique_ptr<Tags>{new Tags()});
    tag.modify()->name = rec.name;
  }

  node.modify()->tag.insert(tag);
  tag.modify()->node.insert(node);

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
    std::vector<int> tagg;
    ret.parent_id = id;
    ret.resource_id = nod->resource_id;
    ret.type = nod->type;
    for (const auto &tg : nod->tag) {
      tagg.push_back(tg.id());
    }
    ret.tag_id = tagg;
    children.push_back(ret);
  }

  transaction.commit();
  return children;
}
