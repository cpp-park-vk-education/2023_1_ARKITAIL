#include "DbMock.hpp"

DbMock::DbMock() {
	users.emplace_back(0, 1, "uma_op", "bannikovtop@gmail.com", "UmaOp", "Arkitail");
	users.emplace_back(1, 2, "uma_test", "test@gmail.com", "Test", "Test");

	nodes.emplace_back(0, 0, 0, NodeType::ROOT);
	nodes.emplace_back(1, 1, 1, NodeType::ROOT);
	nodes.emplace_back(2, 2, 2, NodeType::ROOT);
	nodes.emplace_back(3, 1, 3, NodeType::PRIVATE_GROUP);
	nodes.emplace_back(4, 1, 4, NodeType::PUBLIC_GROUP);
	nodes.emplace_back(5, 1, 5, NodeType::SUBSCRIPTIONS_GROUP);
	nodes.emplace_back(6, 1, 6, NodeType::PROFILE_GROUP);
	nodes.emplace_back(7, 3, 7, NodeType::PRIVATE_DIRECTORY);
	nodes.emplace_back(8, 7, 1, NodeType::PRIVATE_CALENDAR);
	nodes.emplace_back(9, 3, 2, NodeType::PRIVATE_CALENDAR);
	nodes.emplace_back(10, 4, 8, NodeType::PUBLIC_DIRECTORY);
	nodes.emplace_back(11, 10, 3, NodeType::PUBLIC_CALENDAR);
	nodes.emplace_back(12, 4, 4, NodeType::PUBLIC_CALENDAR);
	nodes.emplace_back(13, 5, 22, NodeType::MOUNT);
	nodes.emplace_back(14, 6, 0, NodeType::PROFILE);
	nodes.emplace_back(15, 2, 9, NodeType::PRIVATE_GROUP);
	nodes.emplace_back(16, 2, 10, NodeType::PUBLIC_GROUP);
	nodes.emplace_back(17, 2, 11, NodeType::SUBSCRIPTIONS_GROUP);
	nodes.emplace_back(18, 2, 12, NodeType::PROFILE_GROUP);
	nodes.emplace_back(19, 15, 13, NodeType::PRIVATE_DIRECTORY);
	nodes.emplace_back(20, 19, 5, NodeType::PRIVATE_CALENDAR);
	nodes.emplace_back(21, 15, 6, NodeType::PRIVATE_CALENDAR);
	nodes.emplace_back(22, 16, 14, NodeType::PUBLIC_DIRECTORY);
	nodes.emplace_back(23, 22, 7, NodeType::PUBLIC_CALENDAR);
	nodes.emplace_back(24, 16, 8, NodeType::PUBLIC_CALENDAR);
	nodes.emplace_back(25, 17, 10, NodeType::MOUNT);
	nodes.emplace_back(26, 18, 0, NodeType::PROFILE);

	directories.emplace_back(0, 0, 0, "", "");
	directories.emplace_back(1, 1, 0, "UmaOpRoot", "desc");
	directories.emplace_back(2, 2, 1, "TestRoot", "desc");
	directories.emplace_back(3, 3, 0, "UmaOpPrivate", "desc");
	directories.emplace_back(4, 4, 0, "UmaOpPublic", "desc");
	directories.emplace_back(5, 5, 0, "UmaOpSubscriptions", "desc");
	directories.emplace_back(6, 6, 0, "UmaOpProfile", "desc");
	directories.emplace_back(7, 7, 0, "PrivateDirecotry", "desc");
	directories.emplace_back(8, 10, 0, "PublicDirectory", "desc");
	directories.emplace_back(9, 15, 1, "TestPrivate", "desc");
	directories.emplace_back(10, 16, 1, "TestPublic", "desc");
	directories.emplace_back(11, 17, 1, "TestSubscriptions", "desc");
	directories.emplace_back(12, 18, 1, "TestProfile", "desc");
	directories.emplace_back(13, 19, 1, "PrivateDirectory", "desc");
	directories.emplace_back(14, 22, 1, "PublicDirectory", "desc");
	
	calendars.emplace_back(0, 0, 0, "", "");
	calendars.emplace_back(1, 8, 0, "PrivateCalendar", "desc");
	calendars.emplace_back(2, 9, 0, "PrivateCalendar", "desc");
	calendars.emplace_back(3, 11, 0, "PublicCalendar", "desc");
	calendars.emplace_back(4, 12, 0, "PublicCalendar", "desc");
	calendars.emplace_back(5, 20, 1, "PrivateCalendar", "desc");
	calendars.emplace_back(6, 21, 1, "PrivateCalendar", "desc");
	calendars.emplace_back(7, 23, 1, "PublicCalendar", "desc");
	calendars.emplace_back(8, 24, 1, "PublicCalendar", "desc");

	events.emplace_back(0, 0, "", "", std::chrono::steady_clock::now(), std::chrono::steady_clock::now());
}

