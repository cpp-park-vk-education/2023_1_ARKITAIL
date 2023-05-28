#include <algorithm>
#include <iostream>
#include <thread>

#include "DbManagers.hpp"
#include "IDirectoryDbManager.hpp"
#include "INodeDbManager.hpp"
#include "IUserDbManager.hpp"
#include "SessionScopeMap.hpp"

DbManagers::DbManagers(
	std::unique_ptr<IUserDbManager> user_dbm,
	std::unique_ptr<INodeDbManager> node_dbm,
	std::unique_ptr<IDirectoryDbManager> directory_dbm,
	std::unique_ptr<ICalendarDbManager> calendar_dbm,
	std::unique_ptr<IEventDbManager> event_dbm,
	std::unique_ptr<ICommentDbManager> comment_dbm,
	std::unique_ptr<ITagDbManager> tag_dbm,
	std::unique_ptr<IProfileDbManager> profile_dbm
) :
	user_dbm_(std::move(user_dbm)),
	node_dbm_(std::move(node_dbm)),
	directory_dbm_(std::move(directory_dbm)),
	calendar_dbm_(std::move(calendar_dbm)),
	event_dbm_(std::move(event_dbm)),
	comment_dbm_(std::move(comment_dbm)),
	tag_dbm_(std::move(tag_dbm)),
	profile_dbm_(std::move(profile_dbm)) {}

IUserDbManager* DbManagers::user_dbm() {
	return user_dbm_.get();
}

INodeDbManager* DbManagers::node_dbm() {
	return node_dbm_.get();
}

IDirectoryDbManager* DbManagers::directory_dbm() {
	return directory_dbm_.get();
}

ICalendarDbManager* DbManagers::calendar_dbm() {
	return calendar_dbm_.get();
}

IEventDbManager* DbManagers::event_dbm() {
	return event_dbm_.get();
}

ICommentDbManager* DbManagers::comment_dbm() {
	return comment_dbm_.get();
}

ITagDbManager* DbManagers::tag_dbm() {
	return tag_dbm_.get();
}

IProfileDbManager* DbManagers::profile_dbm() {
	return profile_dbm_.get();
}

