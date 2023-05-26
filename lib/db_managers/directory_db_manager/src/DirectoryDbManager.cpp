#include "DirectoryDbManager.hpp"


int DirectoryDbManager::add(const Directory &ret) {
  dbo::Transaction transaction(session_);

  std::unique_ptr<Directories> direct{new Directories()};
  direct->description = ret.description;
  direct->name = ret.name;
  direct->node = session_.find<Nodes>("id = ?").bind(ret.node_id);
  direct->user = session_.find<Users>("id = ?").bind(ret.owner_id);
  dbo::ptr<Directories> directPtr = session_.add(std::move(direct));
  session_.flush();
  transaction.commit();
  id_ = directPtr.id();
  return id_;
}

void DirectoryDbManager::remove(int directory_id) {
  dbo::Transaction transaction(session_);

  dbo::ptr<Directories> direct =
      session_.find<Directories>().where("id = ?").bind(directory_id);
  if (!direct) {
    return;
  }
  direct.remove();
  transaction.commit();
}

void DirectoryDbManager::update(const Directory &ret) {
  dbo::Transaction transaction(session_);

  dbo::ptr<Directories> direct =
      session_.find<Directories>().where("id = ?").bind(ret.id);
  if (!direct) {
    return;
  }
  direct.modify()->user = session_.find<Users>().where("id = ?").bind(ret.owner_id);
  direct.modify()->name = ret.name;
  direct.modify()->description = ret.description;
  direct.modify()->node = session_.find<Nodes>().where("id = ?").bind(ret.node_id);
  transaction.commit();
}

const Directory& DirectoryDbManager::get(int directory_id) {
  dbo::Transaction transaction(session_);

  Directory ret;
  dbo::ptr<Directories> direct =
      session_.find<Directories>().where("id = ?").bind(directory_id);
  if (!direct) {
    return ret;
  }
  ret.name = direct->name;
  ret.owner_id = direct->user.id();
  ret.description = direct->description;
  ret.node_id = direct->node.id();

  transaction.commit();

  return ret;
}