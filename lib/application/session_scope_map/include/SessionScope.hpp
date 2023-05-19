#pragma once

#include "DbManagers.hpp"
#include "Managers.hpp"
#include "ConnectionsMediator.hpp"

class SessionScope {
public:
	SessionScope();

	Managers managers;
	DbManagers db_managers;
	ConnectionsMediator connections_mediator;

};

