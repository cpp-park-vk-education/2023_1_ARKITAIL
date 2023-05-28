#include "SessionScope.hpp"

#include <memory>

#include <Wt/Dbo/Session.h>

#include "IManagers.hpp"
#include "ConnectionsMediator.hpp"

SessionScope::SessionScope(
	std::unique_ptr<IManagers> managers,
	std::unique_ptr<ConnectionsMediator> connections_mediator,
  std::unique_ptr<Wt::Dbo::Session> session
) :
	managers_(std::move(managers)),
	connections_mediator_(std::move(connections_mediator)),
  session_(std::move(session)) {}

IManagers* SessionScope::managers() {
	return managers_.get();
}

ConnectionsMediator* SessionScope::connections_mediator() {
	return connections_mediator_.get();
}

Wt::Dbo::Session* SessionScope::session() {
	return session_.get();
}

