#pragma once

#include "IManagers.hpp"
#include "Managers.hpp"
#include "ConnectionsMediator.hpp"
#include <memory>

class SessionScope {
public:
	SessionScope(
		std::unique_ptr<IManagers> managers,
		std::unique_ptr<ConnectionsMediator> connections_mediator
	);

	IManagers* managers();
	ConnectionsMediator* connections_mediator();

private:
	std::unique_ptr<IManagers> managers_;
	std::unique_ptr<ConnectionsMediator> connections_mediator_;

};

