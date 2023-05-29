#include "TagManager.hpp"
#include "IDbManagers.hpp"
#include "Tag.hpp"
#include <cstddef>
#include <memory>

TagManager::TagManager(std::shared_ptr<IDbManagers> db) :
	db_(db) {}

TagSptr TagManager::get(size_t tag_id) {
	return db_->tag_dbm()->get(tag_id);
}

size_t TagManager::add(TagSptr tag) {
	return db_->tag_dbm()->add(tag);
}

void TagManager::remove(size_t tag_id) {
	db_->tag_dbm()->remove(tag_id);
}

