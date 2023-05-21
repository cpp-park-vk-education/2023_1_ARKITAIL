#include "nodeDbManager.hpp"

int NodeManager::add(Ret_Node &ret) {
  Ret_Tag t_ret;
  dbo::Transaction transaction(session_);

  std::unique_ptr<nodes> node{new nodes()};
  node->parent = session_.find<nodes>().where("id = ?").bind(ret.parent_id);
  node->resource_id = ret.resource_id;
  node->type = ret.type;

  dbo::ptr<nodes> nodePtr = session_.add(std::move(node));
      nodePtr = session_.find<nodes>().where("resource_id = ?").bind(ret.resource_id);

  id = nodePtr.id();
  transaction.commit();

  return id;
}

void NodeManager::remove(const int id) {
  dbo::Transaction transaction(session_);

  dbo::ptr<nodes> node = session_.find<nodes>().where("id = ?").bind(id);

  node.remove();
  transaction.commit();
}

void NodeManager::update(Ret_Node &ret) {
  dbo::Transaction transaction(session_);

  dbo::ptr<nodes> node =
      session_.find<nodes>().where("resource_id = ?").bind(ret.resource_id);

  node.modify()->parent =
      session_.find<nodes>().where("id = ?").bind(ret.parent_id);
  node.modify()->resource_id = ret.resource_id;
  node.modify()->type = ret.type;

  transaction.commit();
}

Ret_Node NodeManager::get(const int id) {
  dbo::Transaction transaction(session_);

  std::vector<int> tagv;
  Ret_Node ret;
  dbo::ptr<nodes> node = session_.find<nodes>().where("id = ?").bind(id);
  ret.parent_id = node->parent.id();
  ret.type = node->type;
  ret.resource_id = node->resource_id;
  for (int i = 0; i < node->tag.size(); ++i) {
    dbo::ptr<tags> id = session_.find<tags>().where("node_id = ?").bind(id);
    tagv.push_back(id.id());
  }
  ret.tag_id = tagv;

  transaction.commit();

  return ret;
}

void NodeManager::tag(const int id, Ret_Tag &rec) {
  dbo::Transaction transaction(session_);

  dbo::ptr<tags> tag = session_.find<tags>().where("name = ?").bind(rec.name);
  dbo::ptr<nodes> node = session_.find<nodes>().where("id = ?").bind(id);

  if (!tag) {
    tag = session_.add(std::unique_ptr<tags>{new tags()});
    tag.modify()->name = rec.name;
  }

  node.modify()->tag.insert(tag);
  tag.modify()->node.insert(node);

  transaction.commit();
}

void NodeManager::move(const int id, const int destination_id) {
  dbo::Transaction transaction(session_);

  dbo::ptr<nodes> node = session_.find<nodes>().where("id = ?").bind(id);

  node.modify()->parent =
      session_.find<nodes>().where("id = ?").bind(destination_id);

  transaction.commit();
}

std::vector<Ret_Node> NodeManager::getChildren(const int id) {
  dbo::Transaction transaction(session_);
  Ret_Node ret;
  std::vector<Ret_Node> children;
  dbo::collection<dbo::ptr<nodes>> node =
      session_.find<nodes>().where("parent = ?").bind(id);
  for (const dbo::ptr<nodes> &nod : node) {
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
