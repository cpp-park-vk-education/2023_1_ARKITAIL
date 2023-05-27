#include "CommentDbManagerMock.hpp"
#include "Comment.hpp"
#include "ICommentDbManager.hpp"

CommentDbManagerMock::CommentDbManagerMock() :
	data_(),
	aid_(1) {
	
	data_.emplace_back(0, 0, "");
}

CommentSptr CommentDbManagerMock::get(int comment_id) {
	for (auto e = data_.begin() + 1; e != data_.end(); e++)
		if (e->id == comment_id)
			return std::make_shared<Comment>(*e);
	
	return std::make_shared<Comment>(data_[0]);
}

int CommentDbManagerMock::add(CommentSptr comment) {
	data_.emplace_back(
		aid_,
		comment->event_id,
		//comment.owner_id,
		comment->text
	);

	return aid_++;
}

// void CommentDbManagerMock::update(CommentSptr comment) {
// 	for (auto e : data_)
// 		if (e.id == comment.id)
// 			e = comment;
// }

void CommentDbManagerMock::remove(int comment_id) {
	for (auto e = data_.begin() + 1; e != data_.end(); e++)
		if (e->id == comment_id)
			data_.erase(e);
}

