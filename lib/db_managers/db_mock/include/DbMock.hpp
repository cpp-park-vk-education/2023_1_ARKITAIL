#pragma once

#include <vector>

#include "Calendar.hpp"
#include "Comment.hpp"
#include "Directory.hpp"
#include "Event.hpp"
#include "Node.hpp"
#include "Profile.hpp"
#include "Tag.hpp"
#include "User.hpp"

class DbMock {
public:
	DbMock();

	std::vector<User> users;
	std::vector<Node> nodes;
	std::vector<Directory> directories;
	std::vector<Calendar> calendars;
	std::vector<Event> events;
	std::vector<Comment> comments;
	std::vector<Tag> tags;
	std::vector<Profile> profiles;
	std::vector<std::pair<int, int>> tags_to_nodes;
};

