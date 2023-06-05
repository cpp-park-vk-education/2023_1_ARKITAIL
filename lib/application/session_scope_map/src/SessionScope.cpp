#include "SessionScope.hpp"

#include <memory>

#include "IManagers.hpp"
#include "ConnectionsMediator.hpp"
#include "Session.hpp"

SessionScope::SessionScope(
	std::unique_ptr<IManagers> managers,
	std::unique_ptr<ConnectionsMediator> connections_mediator,
  std::unique_ptr<Session> session
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

Session* SessionScope::session() {
	return session_.get();
}

