#include "TagDbManagerMock.hpp"

TagDbManagerMock::TagDbManagerMock() :
	data_(),
	aid_(1) {

	data_.emplace_back(0, "");
}

const Tag& TagDbManagerMock::get(int tag_id) {
	for (auto e = data_.begin() + 1; e != data_.end(); e++)
		if (e->id == tag_id)
			return *e;
	
	return data_[0];
}

int TagDbManagerMock::add(const Tag& tag) {
	data_.emplace_back(
		aid_,
		tag.name
	);

	return aid_++;
}

// void TagDbManagerMock::update(const Tag& tag) {
// 	for (auto e : data_)
// 		if (e.id == tag.id)
// 			e = tag;
// }

void TagDbManagerMock::remove(int tag_id) {
	for (auto e = data_.begin() + 1; e != data_.end(); e++)
		if (e->id == tag_id)
			data_.erase(e);
}

