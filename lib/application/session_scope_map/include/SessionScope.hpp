#pragma once

#include <memory>

#include "ConnectionsMediator.hpp"
#include "IManagers.hpp"
#include "Session.hpp"

class SessionScope {
public:
	SessionScope(
		std::unique_ptr<IManagers> managers,
		std::unique_ptr<ConnectionsMediator> connections_mediator,
    std::unique_ptr<Session> session
	);

	IManagers* managers();
	ConnectionsMediator* connections_mediator();
  Session* session();

private:
	std::unique_ptr<IManagers> managers_;
	std::unique_ptr<ConnectionsMediator> connections_mediator_;
  std::unique_ptr<Session> session_;

};

