#pragma once

#include "IUserManager.hpp"
#include "IDirectoryManager.hpp"
#include "ICalendarManager.hpp"
#include "INodeManager.hpp"

class Managers {
public:
	static Managers& instance();

	IUserManager* user_manager;
	IDirectoryManager* directory_manager;
	ICalendarManager* calendar_manager;
	INodeManager* node_manager;

};

