#pragma once

#include <memory>

#include "IUserDbManager.hpp"
#include "INodeDbManager.hpp"
#include "IDirectoryDbManager.hpp"
#include "ICalendarDbManager.hpp"
#include "IEventDbManager.hpp"
#include "ICommentDbManager.hpp"
#include "ITagDbManager.hpp"
#include "IProfileDbManager.hpp"

class DbManagers {
public:
	DbManagers(
		std::unique_ptr<IUserDbManager> user_dbm,
		std::unique_ptr<INodeDbManager> node_dbm,
		std::unique_ptr<IDirectoryDbManager> directory_dbm,
		std::unique_ptr<ICalendarDbManager> calendar_dbm,
		std::unique_ptr<IEventDbManager> event_dbm,
		std::unique_ptr<ICommentDbManager> comment_dbm,
		std::unique_ptr<ITagDbManager> tag_dbm,
		std::unique_ptr<IProfileDbManager> profile_dbm
	);

	static DbManagers& instance();

	std::unique_ptr<IUserDbManager> user_dbm;
	std::unique_ptr<INodeDbManager> node_dbm;
	std::unique_ptr<IDirectoryDbManager> directory_dbm;
	std::unique_ptr<ICalendarDbManager> calendar_dbm;
	std::unique_ptr<IEventDbManager> event_dbm;
	std::unique_ptr<ICommentDbManager> comment_dbm;
	std::unique_ptr<ITagDbManager> tag_dbm;
	std::unique_ptr<IProfileDbManager> profile_dbm;

};
 
