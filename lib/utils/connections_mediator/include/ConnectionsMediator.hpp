#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WSignal.h>

#include "ConnectionPoint.hpp"

class ConnectionsMediator {
public:
	ConnectionsMediator();

	void connect();
	
	// Declare your connetion points there 
	ConnectionPoint<Wt::Signal<int>, Wt::WContainerWidget, int> cp;

};

