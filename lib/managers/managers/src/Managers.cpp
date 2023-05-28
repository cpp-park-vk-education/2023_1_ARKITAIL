#include "Managers.hpp"

#include <algorithm>
#include <memory>
#include <thread>

#include "IEventManager.hpp"
#include "SessionScopeMap.hpp"

Managers::Managers(
	std::unique_ptr<IUserManager> user_manager,
	std::unique_ptr<INodeManager> node_manager,
	std::unique_ptr<IDirectoryManager> directory_manager,
	std::unique_ptr<ICalendarManager> calendar_manager,
	std::unique_ptr<IEventManager> event_manager,
	std::unique_ptr<IProfileManager> profile_manager
) :
	user_manager_(std::move(user_manager)),
	node_manager_(std::move(node_manager)),
	directory_manager_(std::move(directory_manager)),
	calendar_manager_(std::move(calendar_manager)),
	event_manager_(std::move(event_manager)),
	profile_manager_(std::move(profile_manager)) {}

IUserManager* Managers::user_manager() {
	return user_manager_.get();
}

INodeManager* Managers::node_manager() {
	return node_manager_.get();
}

IDirectoryManager* Managers::directory_manager() {
	return directory_manager_.get();
}

ICalendarManager* Managers::calendar_manager() {
	return calendar_manager_.get();
}

IEventManager* Managers::event_manager() {
	return event_manager_.get();
}

IProfileManager* Managers::profile_manager() {
	return profile_manager_.get();
}

