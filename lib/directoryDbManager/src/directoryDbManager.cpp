#include "directoryDbManager.hpp"

int DirectoryManager::Add(RetDir &ret) {
  dbo::Transaction transaction(session_);

  std::unique_ptr<Directories> direct{new Directories()};
  direct->name = ret.name;
  direct->description = ret.description;

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
  direct.modify()->name = ret.name;
  direct.modify()->description = ret.description;
  
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
  ret.name = direct->name;
  ret.description = direct->description;

  transaction.commit();

  return ret;
}