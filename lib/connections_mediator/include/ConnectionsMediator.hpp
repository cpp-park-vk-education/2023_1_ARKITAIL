#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WSignal.h>

#include "PageWidget.hpp"
#include "ConnectionPoint.hpp"

class ConnectionsMediator {
public:
	ConnectionsMediator();

	static ConnectionsMediator& instance();

	void connect();
	
	// Declare your connetion points there 
	ConnectionPoint<Wt::Signal<int>, Wt::WContainerWidget, int> cp;

};

