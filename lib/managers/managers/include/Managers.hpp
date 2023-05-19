#pragma once

#include <memory>

#include "IUserManager.hpp"
#include "IDirectoryManager.hpp"
#include "ICalendarManager.hpp"
#include "INodeManager.hpp"

class Managers {
public:
	Managers(
		std::unique_ptr<IUserManager> user_manager,
		std::unique_ptr<INodeManager> node_manager,
		std::unique_ptr<IDirectoryManager> directory_manager,
		std::unique_ptr<ICalendarManager> calendar_manager
	);

	static Managers& instance();

	std::unique_ptr<IUserManager> user_manager;
	std::unique_ptr<INodeManager> node_manager;
	std::unique_ptr<IDirectoryManager> directory_manager;
	std::unique_ptr<ICalendarManager> calendar_manager;

};

