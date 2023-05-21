#pragma once

#include "ICalendarManager.hpp"
#include "IDirectoryManager.hpp"
#include "IEventManager.hpp"
#include "INodeManager.hpp"
#include "IUserManager.hpp"

class IManagers {
public:
	virtual IUserManager* user_manager() = 0;
	virtual INodeManager* node_manager() = 0;
	virtual IDirectoryManager* directory_manager() = 0;
	virtual ICalendarManager* calendar_manager() = 0;
	virtual IEventManager* event_manager() = 0;

	virtual ~IManagers() {}

};

