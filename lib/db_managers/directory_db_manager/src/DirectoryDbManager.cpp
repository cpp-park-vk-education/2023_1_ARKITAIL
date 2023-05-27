#include "DirectoryDbManager.hpp"

#include <Wt/Dbo/Transaction.h>

#include "Directory.hpp"

int DirectoryDbManager::add(DirectorySptr directory) {
  Wt::Dbo::Transaction transaction(session_);

  std::unique_ptr<db::Directory> db_directory_unique
     = std::make_unique<db::Directory>();

  db_directory_unique->description = directory->description;
  db_directory_unique->name = directory->name;
  db_directory_unique->node
      = session_.find<db::Node>("id = ?").bind(directory->node_id);

  db_directory_unique->user
      = session_.find<db::User>("id = ?").bind(directory->owner_id);

  db::DirectoryPtr db_directory = session_.add(std::move(db_directory_unique));
  session_.flush();

  transaction.commit();

  id_ = db_directory.id();
  return id_;
}

void DirectoryDbManager::remove(int directory_id) {
  Wt::Dbo::Transaction transaction(session_);

  db::DirectoryPtr db_directory =
      session_.find<db::Directory>().where("id = ?").bind(directory_id);

  if (!db_directory) {
    return;
  }

  db_directory.remove();

  transaction.commit();
}

void DirectoryDbManager::update(DirectorySptr directory) {
  Wt::Dbo::Transaction transaction(session_);

  db::DirectoryPtr db_directory =
      session_.find<db::Directory>().where("id = ?").bind(directory->id);

  if (!db_directory) {
    return;
  }

  db_directory.modify()->user
      = session_.find<db::User>().where("id = ?").bind(directory->owner_id);

  db_directory.modify()->name = directory->name;
  db_directory.modify()->description = directory->description;
  db_directory.modify()->node
      = session_.find<db::Node>().where("id = ?").bind(directory->node_id);

  transaction.commit();
}

DirectorySptr DirectoryDbManager::get(int directory_id) {
  db::DirectoryPtr db_directory =
      session_.find<db::Directory>().where("id = ?").bind(directory_id);

  if (!db_directory) {
    return nullptr;
  }

  Directory directory;
  directory.name = db_directory->name;
  directory.owner_id = db_directory->user.id();
  directory.description = db_directory->description;
  directory.node_id = db_directory->node.id();
  directory.id = directory_id;

  return std::make_shared<Directory>(std::move(directory));
}
