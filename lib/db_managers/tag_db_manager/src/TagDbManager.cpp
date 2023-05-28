#include "TagDbManager.hpp"

#include <memory>

#include "DbModels.hpp"
#include "Tag.hpp"

int TagDbManager::add(TagSptr tag) {
  Wt::Dbo::Transaction transaction(session_);

  std::unique_ptr<db::Tag> db_tag_unique = std::make_unique<db::Tag>();
  db_tag_unique->name = tag->name;

  db::TagPtr db_tag = session_.add(std::move(db_tag_unique));
  session_.flush();

  transaction.commit();

  id_ = db_tag.id();
  return id_;
}

void TagDbManager::remove(int tag_id) {
  Wt::Dbo::Transaction transaction(session_);

  db::TagPtr db_tag
      = session_.find<db::Tag>().where("id = ?").bind(tag_id);

  if (!db_tag) {
    return;
  }

  db_tag.remove();

  transaction.commit();
}

void TagDbManager::update(TagSptr tag) {
  // TODO(Antiho)
}

TagSptr TagDbManager::get(int tag_id) {
  db::TagPtr db_tag
      = session_.find<db::Tag>().where("id = ?").bind(tag_id);

  if (!db_tag) {
    return nullptr;
  }

  TagSptr tag = std::make_shared<Tag>();
  tag->name = tag->name;
  tag->id = tag_id;
  
  return tag;
}
