#include "SessionScopeMap.hpp"
#include "Managers.hpp"
#include <algorithm>
#include <thread>

Managers::Managers(
	std::unique_ptr<IUserManager> user_manager,
	std::unique_ptr<INodeManager> node_manager,
	std::unique_ptr<IDirectoryManager> directory_manager,
	std::unique_ptr<ICalendarManager> calendar_manager
) :
	user_manager_(std::move(user_manager)),
	node_manager_(std::move(node_manager)),
	directory_manager_(std::move(directory_manager)),
	calendar_manager_(std::move(calendar_manager)) {}

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

