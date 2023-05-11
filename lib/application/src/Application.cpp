#include <string>

#include "Application.hpp"
#include "ConnectionsMediator.hpp"

Application::Application(const Wt::WEnvironment& env) :
	Wt::WApplication(env) {

	// Some initial widgets configuration

	// Connections mediator connections establishing
	ConnectionsMediator::instance().connect();
	
}

void Application::route(const std::string& internalPath) {
	
}

