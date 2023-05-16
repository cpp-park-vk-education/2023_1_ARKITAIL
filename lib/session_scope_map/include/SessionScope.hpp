#pragma once

#include "Managers.hpp"
#include "ConnectionsMediator.hpp"

class SessionScope {
public:
	SessionScope();

	Managers managers;
	ConnectionsMediator connections_mediator;

};

