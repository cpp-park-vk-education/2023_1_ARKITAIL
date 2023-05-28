#pragma once

#include "ICalendarDbManager.hpp"
#include "ICommentDbManager.hpp"
#include "IDirectoryDbManager.hpp"
#include "IEventDbManager.hpp"
#include "INodeDbManager.hpp"
#include "IProfileDbManager.hpp"
#include "ITagDbManager.hpp"
#include "IUserDbManager.hpp"

class IDbManagers {
public:
	
	virtual IUserDbManager* user_dbm() = 0;
	virtual INodeDbManager* node_dbm() = 0;
	virtual IDirectoryDbManager* directory_dbm() = 0;
	virtual ICalendarDbManager* calendar_dbm() = 0;
	virtual IEventDbManager* event_dbm() = 0;
	virtual ICommentDbManager* comment_dbm() = 0;
	virtual ITagDbManager* tag_dbm() = 0;
	virtual IProfileDbManager* profile_dbm() = 0;

	virtual ~IDbManagers() {}

};

