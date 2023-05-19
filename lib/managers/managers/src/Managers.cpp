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
	user_manager(std::move(user_manager)),
	node_manager(std::move(node_manager)),
	directory_manager(std::move(directory_manager)),
	calendar_manager(std::move(calendar_manager)) {}

Managers& Managers::instance() {
	return SessionScopeMap::instance().get(std::this_thread::get_id())->managers;
}

