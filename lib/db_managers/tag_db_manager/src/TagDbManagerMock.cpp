#include "TagDbManagerMock.hpp"
#include "DbMock.hpp"
#include "Node.hpp"
#include "Tag.hpp"
#include <memory>
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

void TagDbManagerMock::remove(int tag_id) {
	for (auto e = db_->tags.begin() + 1; e != db_->tags.end(); e++)
		if (e->id == tag_id) {
			db_->tags.erase(e);
			break;
		}
}

std::vector<NodeSptr> TagDbManagerMock::nodeByTag(int tag_id) {
	std::vector<NodeSptr> ns;

	for (auto tn : db_->tags_to_nodes)
		if (tn.first == tag_id)
			for (auto e = db_->nodes.begin() + 1; e != db_->nodes.end(); e++)
			    if (e->id == tn.second) {
					ns.push_back(std::make_shared<Node>(*e));
					break;
				}

	return ns;
}

TagSptr TagDbManagerMock::find(const std::string& tag_name) {
	for (auto e = db_->tags.begin() + 1; e != db_->tags.end(); e++)
		if (e->name == tag_name)
			return std::make_shared<Tag>(*e);
	
	return std::make_shared<Tag>(db_->tags[0]);
}
