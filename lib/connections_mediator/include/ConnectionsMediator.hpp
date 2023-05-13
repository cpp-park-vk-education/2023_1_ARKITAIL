#pragma once

#include "PageWidget.hpp"
#include "ConnectionPoint.hpp"
#include <Wt/WSignal.h>

class ConnectionsMediator {
public:
	static ConnectionsMediator& instance();

	void connect();
	
	// Declare your connetion points there 
	ConnectionPoint<Wt::Signal<int>, PageWidget, int> cp;

private:
	ConnectionsMediator();

};

