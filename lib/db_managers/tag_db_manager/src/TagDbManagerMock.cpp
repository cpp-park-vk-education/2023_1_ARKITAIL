#include "TagDbManagerMock.hpp"
#include "DbMock.hpp"
#include <vector>

TagDbManagerMock::TagDbManagerMock(std::shared_ptr<DbMock> db) :
	db_(db),
	aid_(db->tags_to_nodes.size()) {}

TagSptr TagDbManagerMock::get(int tag_id) {
	for (auto e = db_->tags.begin() + 1; e != db_->tags.end(); e++)
		if (e->id == tag_id)
			return std::make_shared<Tag>(*e);
	
	return std::make_shared<Tag>(db_->tags[0]);
}

int TagDbManagerMock::add(TagSptr tag) {
	db_->tags.emplace_back(
		aid_,
		tag->name
	);

	return aid_++;
}

void TagDbManagerMock::update(TagSptr tag) {
	for (auto e : db_->tags)
		if (e.id == tag->id)
			e = *tag;
}

void TagDbManagerMock::remove(int tag_id) {
	for (auto e = db_->tags.begin() + 1; e != db_->tags.end(); e++)
		if (e->id == tag_id)
			db_->tags.erase(e);
}

std::vector<Node> TagDbManagerMock::NodeByTag(int tag_id) {
	return std::vector<Node>();
}

Tag TagDbManagerMock::find(const std::string title) {
	for (auto e = db_->tags.begin() + 1; e != db_->tags.end(); e++)
		if (e->name == title)
			return *e;
	
	return db_->tags[0];
}
