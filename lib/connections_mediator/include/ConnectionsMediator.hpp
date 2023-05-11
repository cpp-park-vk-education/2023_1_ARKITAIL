#pragma once

class ConnectionsMediator {
public:
	static ConnectionsMediator& instance();

	void connect();
	
	// Declare your connetion points there 

private:
	ConnectionsMediator();

};

