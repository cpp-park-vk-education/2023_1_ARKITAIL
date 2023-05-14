#include <Wt/WWidget.h>
#include <string>

#include "Application.hpp"
#include "ConnectionsMediator.hpp"
#include "PageWidget.hpp"

Application::Application(const Wt::WEnvironment& env) :
	Wt::WApplication(env),
	session_(),
	pages_(), 
	cur_swap_(),
	cur_page_(nullptr),
	navbar_() {

	// Some initial widgets configuration
	pages_.emplace("/helo", std::make_unique<PageWidget>("/bui")).first->second.set_destination(&cur_swap_);
	pages_.emplace("/bui", std::make_unique<PageWidget>("/helo")).first->second.set_destination(&cur_swap_);

	// Main page configuration
	pages_["/helo"].build_destination();
	cur_swap_.swap();
	cur_page_ = root()->addWidget(cur_swap_.get_content());

	internalPathChanged().connect(this, &Application::route);

	// Connections mediator connections establishing
	ConnectionsMediator::instance().connect();
}

void Application::route(const std::string& internalPath) {
	cur_swap_.set_content(root()->removeWidget(cur_page_));
	cur_swap_.swap();
	pages_[internalPath].build_destination();
	cur_swap_.swap();
	cur_page_ = root()->addWidget(cur_swap_.get_content());
}

