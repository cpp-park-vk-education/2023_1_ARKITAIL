#include <thread>

#include "SessionScopeMap.hpp"
#include "ConnectionsMediator.hpp"

ConnectionsMediator::ConnectionsMediator() :
	cp() {}

ConnectionsMediator& ConnectionsMediator::instance() {
	return SessionScopeMap::instance().get(std::this_thread::get_id())->connections_mediator;
}

void ConnectionsMediator::connect() {
	cp.connect();
}

