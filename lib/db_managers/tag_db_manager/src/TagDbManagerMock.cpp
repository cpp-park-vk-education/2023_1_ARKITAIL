#include "TagDbManagerMock.hpp"
#include "DbMock.hpp"
#include <vector>

TagDbManagerMock::TagDbManagerMock(std::shared_ptr<DbMock> db) :
	db_(db),
	aid_(db->tags_to_nodes.size()) {}

const Tag& TagDbManagerMock::get(size_t tag_id) {
	for (auto e = db_->tags.begin() + 1; e != db_->tags.end(); e++)
		if (e->id == tag_id)
			return *e;
	
	return db_->tags[0];
}

size_t TagDbManagerMock::add(const Tag& tag) {
	db_->tags.emplace_back(
		aid_,
		tag.name
	);

	return aid_++;
}

void TagDbManagerMock::update(const Tag& tag) {
	for (auto e : db_->tags)
		if (e.id == tag.id)
			e = tag;
}

void TagDbManagerMock::remove(size_t tag_id) {
	for (auto e = db_->tags.begin() + 1; e != db_->tags.end(); e++)
		if (e->id == tag_id)
			db_->tags.erase(e);
}

std::vector<Node> TagDbManagerMock::NodeByTag(size_t tag_id) {
	return std::vector<Node>();
}

