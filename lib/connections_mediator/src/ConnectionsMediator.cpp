#include "ConnectionsMediator.hpp"

ConnectionsMediator::ConnectionsMediator() :
	cp() {}

ConnectionsMediator& ConnectionsMediator::instance() {
	static ConnectionsMediator cm;
	return cm;
}

void ConnectionsMediator::connect() {
	cp.connect();
}

