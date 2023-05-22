#include "directoryDbManager.hpp"

int DirectoryManager::Add(RetDir &ret) {
  dbo::Transaction transaction(session_);

  std::unique_ptr<Directories> direct{new Directories()};
  direct->name = ret.name;
  direct->description = ret.description;
  direct->node = session_.find<Nodes>("id = ?").bind(ret.node_id);
  direct->user = session_.find<Users>("id = ?").bind(ret.owner_id);
  dbo::ptr<Directories> directPtr = session_.add(std::move(direct));
  session_.flush();
  transaction.commit();
  id_ = directPtr.id();
  return id_;
}

void DirectoryManager::Remove(int id) {
  dbo::Transaction transaction(session_);

  dbo::ptr<Directories> direct =
      session_.find<Directories>().where("id = ?").bind(id);
  if (!direct) {
    return;
  }
  direct.remove();
  transaction.commit();
}

void DirectoryManager::Update(RetDir &ret) {
  dbo::Transaction transaction(session_);

  dbo::ptr<Directories> direct =
      session_.find<Directories>().where("name = ?").bind(ret.name);
  if (!direct) {
    return;
  }
  direct.modify()->user = session_.find<Users>().where("id = ?").bind(ret.owner_id);
  direct.modify()->name = ret.name;
  direct.modify()->description = ret.description;
  direct.modify()->node = session_.find<Nodes>().where("id = ?").bind(ret.node_id);
  transaction.commit();
}

RetDir DirectoryManager::Get(int id) {
  dbo::Transaction transaction(session_);

  RetDir ret;
  dbo::ptr<Directories> direct =
      session_.find<Directories>().where("id = ?").bind(id);
  if (!direct) {
    ret.name = "error";
    return ret;
  }
  ret.owner_id = direct->user.id();
  ret.name = direct->name;
  ret.description = direct->description;
  ret.node_id = direct->node.id();

  transaction.commit();

  return ret;
}