#pragma once

#include <memory>

#include <Wt/Dbo/Session.h>

#include "ConnectionsMediator.hpp"
#include "IManagers.hpp"

class SessionScope {
public:
	SessionScope(
		std::unique_ptr<IManagers> managers,
		std::unique_ptr<ConnectionsMediator> connections_mediator,
    std::unique_ptr<Wt::Dbo::Session> session
	);

	IManagers* managers();
	ConnectionsMediator* connections_mediator();
  Wt::Dbo::Session* session();

private:
	std::unique_ptr<IManagers> managers_;
	std::unique_ptr<ConnectionsMediator> connections_mediator_;
  std::unique_ptr<Wt::Dbo::Session> session_;

};

