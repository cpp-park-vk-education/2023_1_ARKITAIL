#include "TagDbManager.hpp"

#include <Wt/Dbo/Transaction.h>
#include <Wt/WLogger.h>
#include <memory>
#include <string>
#include <vector>

#include "DbModels.hpp"
#include "Node.hpp"
#include "Tag.hpp"
#include "Session.hpp"

TagDbManager::TagDbManager(Session& session)
    : session_(session) {
}

int TagDbManager::add(TagSptr tag) {
  Wt::Dbo::Transaction transaction(session_);

  db::TagPtr db_tag = session_.add(std::make_unique<db::Tag>());

  session_.flush();
  int id = static_cast<int>(db_tag.id());

  db_tag.modify()->name = tag->name;

  transaction.commit();

  return id;
}

void TagDbManager::remove(int tag_id) {
  Wt::Dbo::Transaction transaction(session_);

  db::TagPtr db_tag
      = session_.find<db::Tag>().where("id = ?").bind(tag_id);

  if (!db_tag) {
    Wt::log("TagDbManager::remove: not found tag with id = "
        + std::to_string(tag_id));
    return;
  }

  db_tag.remove();

  transaction.commit();
}

// void TagDbManager::update(TagSptr tag) {
//   Wt::Dbo::Transaction transaction(session_);
//   
//   db::TagPtr db_tag
//       = session_.find<db::Tag>().where("id = ?").bind(tag->id);
// 
//   if (!db_tag) {
//     Wt::log("TagDbManager::update: not found tag with id = "
//         + std::to_string(tag->id));
//     return;
//   }
// 
//   db_tag.modify()->name = tag->name;
// 
//   transaction.commit();
// }

TagSptr TagDbManager::get(int tag_id) {
  Wt::Dbo::Transaction transaction(session_);

  db::TagPtr db_tag
      = session_.find<db::Tag>().where("id = ?").bind(tag_id);

  if (!db_tag) {
    Wt::log("TagDbManager::get: not found tag with id = "
        + std::to_string(tag_id));
    return std::make_shared<Tag>();
  }

  Tag tag {
    static_cast<int>(db_tag.id()),
    db_tag->name,
  };

  transaction.commit();

  return std::make_shared<Tag>(std::move(tag));
}

TagSptr TagDbManager::find(const std::string& tag_name) {}

// std::vector<Node> TagDbManager::NodeByTag(int tag_id) {}
std::vector<NodeSptr> TagDbManager::nodeByTag(int tag_id) {}


