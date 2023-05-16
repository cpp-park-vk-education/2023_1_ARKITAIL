#include "Directory_db_manager.hpp"

int directory_manager::addDirectory(Ret_Dir &ret) {
  dbo::Transaction transaction(session_);

  std::unique_ptr<directory> direct{new directory()};
  direct->name = ret.name;
  direct->description = ret.description;
  direct->node = session_.find<nodes>().where("id = ?").bind(ret.node_id);

  dbo::ptr<directory> directPtr = session_.add(std::move(direct));
  id = directPtr.id();
  transaction.commit();

  return id;
}

void directory_manager::removeDirectory(const int id) {
  dbo::Transaction transaction(session_);

  dbo::ptr<directory> direct =
      session_.find<directory>().where("id = ?").bind(id);

  direct.remove();
  transaction.commit();
}

void directory_manager::updateDirectory(Ret_Dir &ret) {
  dbo::Transaction transaction(session_);

  dbo::ptr<directory> direct =
      session_.find<directory>().where("name = ?").bind(ret.name);

  direct.modify()->name = ret.name;
  direct.modify()->description = ret.description;
  direct.modify()->node =
      session_.find<nodes>().where("id = ?").bind(ret.node_id);

  transaction.commit();
}

Ret_Dir directory_manager::getDirectory(const int id) {
  dbo::Transaction transaction(session_);

  Ret_Dir ret;
  dbo::ptr<directory> direct =
      session_.find<directory>().where("id = ?").bind(id);
  ret.name = direct->name;
  ret.description = direct->description;
  ret.node_id = direct->node.id();

  transaction.commit();

  return ret;
}