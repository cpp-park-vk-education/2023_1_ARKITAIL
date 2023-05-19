#include <algorithm>
#include <thread>

#include "DbManagers.hpp"
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
	user_dbm(std::move(user_dbm)),
	node_dbm(std::move(node_dbm)),
	directory_dbm(std::move(directory_dbm)),
	calendar_dbm(std::move(calendar_dbm)),
	event_dbm(std::move(event_dbm)),
	comment_dbm(std::move(comment_dbm)),
	tag_dbm(std::move(tag_dbm)),
	profile_dbm(std::move(profile_dbm)) {}


DbManagers& DbManagers::instance() {
	return SessionScopeMap::instance().get(std::this_thread::get_id())->db_managers;
}

