#include <memory>

#include "SessionScope.hpp"
#include "IManagers.hpp"
#include "ConnectionsMediator.hpp"

SessionScope::SessionScope(
	std::unique_ptr<IManagers> managers,
	std::unique_ptr<ConnectionsMediator> connections_mediator
) :
	managers_(std::move(managers)),
	connections_mediator_(std::move(connections_mediator)) {}

IManagers* SessionScope::managers() {
	return managers_.get();
}

ConnectionsMediator* SessionScope::connections_mediator() {
	return connections_mediator_.get();
}

