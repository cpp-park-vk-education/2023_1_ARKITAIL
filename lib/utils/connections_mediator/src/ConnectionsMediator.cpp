#include <thread>

#include "SessionScopeMap.hpp"
#include "ConnectionsMediator.hpp"

ConnectionsMediator::ConnectionsMediator() :
	cp() {}

void ConnectionsMediator::connect() {
	cp.connect();
}

