#include "SessionScopeMap.hpp"
#include "Managers.hpp"
#include <thread>

Managers& Managers::instance() {
	return SessionScopeMap::instance().get(std::this_thread::get_id())->managers;
}

