#include "directoryDbManager.hpp"

int DirectoryManager::add(Ret_Dir &ret) {
  dbo::Transaction transaction(session_);

  std::unique_ptr<directory> direct{new directory()};
  direct->name = ret.name;
  direct->description = ret.description;
  direct->node = session_.find<nodes>().where("id = ?").bind(ret.node_id);

  dbo::ptr<directory> directPtr = session_.add(std::move(direct));
  session_.flush();
  transaction.commit();
  id = directPtr.id();
  return id;
}

void DirectoryManager::remove(const int id) {
  dbo::Transaction transaction(session_);

  dbo::ptr<directory> direct =
      session_.find<directory>().where("id = ?").bind(id);
  if (!direct) {
    return;
  }
  direct.remove();
  transaction.commit();
}

void DirectoryManager::update(Ret_Dir &ret) {
  dbo::Transaction transaction(session_);

  dbo::ptr<directory> direct =
      session_.find<directory>().where("name = ?").bind(ret.name);
  if (!direct) {
    return;
  }
  direct.modify()->name = ret.name;
  direct.modify()->description = ret.description;
  direct.modify()->node =
      session_.find<nodes>().where("id = ?").bind(ret.node_id);

  transaction.commit();
}

Ret_Dir DirectoryManager::get(const int id) {
  dbo::Transaction transaction(session_);

  Ret_Dir ret;
  dbo::ptr<directory> direct =
      session_.find<directory>().where("id = ?").bind(id);
  if (!direct) {
    ret.name = "error";
    return ret;
  }
  ret.name = direct->name;
  ret.description = direct->description;
  ret.node_id = direct->node.id();

  transaction.commit();

  return ret;
}