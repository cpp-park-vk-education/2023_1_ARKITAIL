#include "ConnectionsMediator.hpp"

ConnectionsMediator::ConnectionsMediator() {}

ConnectionsMediator& ConnectionsMediator::instance() {
	static ConnectionsMediator cm;
	return cm;
}

void ConnectionsMediator::connect() {}

