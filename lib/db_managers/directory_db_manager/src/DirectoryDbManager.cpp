#include "DirectoryDbManager.hpp"

#include <string>

#include <Wt/Dbo/Transaction.h>

#include "DbModels.hpp"
#include "Directory.hpp"

DirectoryDbManager::DirectoryDbManager(Session& session)
    : session_(session) {
}

int DirectoryDbManager::add(DirectorySptr directory) {
  Wt::Dbo::Transaction transaction(session_);

  db::NodePtr db_node
      = session_.find<db::Node>().where("id = ?").bind(directory->node_id);

  if (!db_node) {
    Wt::log("DirectoryDbManager::add: not found directory's node with id = "
        + std::to_string(directory->node_id));
    return -1;
  }

  db::UserPtr db_user
      = session_.find<db::User>().where("id = ?").bind(directory->owner_id);

  if (!db_user) {
    Wt::log("DirectoryDbManager::add: not found directory's user with id = "
        + std::to_string(directory->node_id));
    return -1;
  }

  db::DirectoryPtr db_directory
      = session_.add(std::make_unique<db::Directory>());

  session_.flush();
  int id = db_directory.id();

  db_directory.modify()->node = db_node;
  db_directory.modify()->owner = db_user;

  db_directory.modify()->name = directory->name;
  db_directory.modify()->description = directory->description;

  transaction.commit();

  return id;
}

void DirectoryDbManager::remove(int directory_id) {
  Wt::Dbo::Transaction transaction(session_);

  db::DirectoryPtr db_directory =
      session_.find<db::Directory>().where("id = ?").bind(directory_id);

  if (!db_directory) {
    Wt::log("DirectoryDbManager::remove: not found directory with id = "
        + std::to_string(directory_id));
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
    Wt::log("DirectoryDbManager::update: not found directory with id = "
        + std::to_string(directory->id));
    return;
  }

  db::NodePtr db_node
      = session_.find<db::Node>().where("id = ?").bind(directory->node_id);

  if (!db_node) {
    Wt::log("DirectoryDbManager::update: not found new directory's node with id = "
        + std::to_string(directory->node_id));
    return;
  }

  db::UserPtr db_user
      = session_.find<db::User>().where("id = ?").bind(directory->owner_id);

  if (!db_user) {
    Wt::log("DirectoryDbManager::update: not found new directory's user with id = "
        + std::to_string(directory->node_id));
    return;
  }
  
  db_directory.modify()->node = db_node;
  db_directory.modify()->owner = db_user;

  db_directory.modify()->name = directory->name;
  db_directory.modify()->description = directory->description;

  transaction.commit();
}

DirectorySptr DirectoryDbManager::get(int directory_id) {
  Wt::Dbo::Transaction transaction(session_);
  
  db::DirectoryPtr db_directory =
      session_.find<db::Directory>().where("id = ?").bind(directory_id);

  if (!db_directory) {
    Wt::log("DirectoryDbManager::get: not found directory with id = "
        + std::to_string(directory_id));
    return std::make_shared<Directory>();
  }

  Directory directory {
    static_cast<int>(db_directory.id()),
    static_cast<int>(db_directory->node.id()),
    static_cast<int>(db_directory->owner.id()),

    db_directory->name,
    db_directory->description,
  };

  transaction.commit();

  return std::make_shared<Directory>(std::move(directory));
}
