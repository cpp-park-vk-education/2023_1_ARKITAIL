#include "CommentDbManagerMock.hpp"
#include "Comment.hpp"
#include "ICommentDbManager.hpp"

CommentDbManagerMock::CommentDbManagerMock() :
	data_(),
	aid_(1) {
	
	data_.emplace_back(0, 0, 0, "");
}

const Comment& CommentDbManagerMock::get(size_t comment_id) {
	for (auto e = data_.begin() + 1; e != data_.end(); e++)
		if (e->id == comment_id)
			return *e;
	
	return data_[0];
}

size_t CommentDbManagerMock::add(const Comment& comment) {
	data_.emplace_back(
		aid_,
		comment.event_id,
		comment.owner_id,
		comment.text
	);

	return aid_++;
}

void CommentDbManagerMock::update(const Comment& comment) {
	for (auto e : data_)
		if (e.id == comment.id)
			e = comment;
}

void CommentDbManagerMock::remove(size_t comment_id) {
	for (auto e = data_.begin() + 1; e != data_.end(); e++)
		if (e->id == comment_id)
			data_.erase(e);
}

