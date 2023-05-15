#pragma once

#include <vector>

#include "User.hpp"
#include "Calendar.hpp"
#include "Event.hpp"
#include "Comment.hpp"
#include "Node.hpp"
#include "Directory.hpp"

class Session {};
class NavbarW {};

class DBConnection {};

class IUserDbManager {
public:
	virtual const User& get() = 0;
	
};

class UserDbManager : public IUserDbManager {
public:
	const User& get();

};

class IDirectoryDbManager {
public:
	virtual const Directory& get(size_t) = 0;
	virtual size_t add(const Directory&) = 0;
	virtual void update(const Directory&) = 0;
	virtual void remove(size_t) = 0;

	virtual std::vector<Directory> getChildren() = 0;

};

class DirectoryDbManager : public IDirectoryDbManager {
public:
	const Directory& get(size_t) override;
	size_t add(const Directory&) override;
	void update(const Directory&) override;
	void remove(size_t) override;
	
	std::vector<Directory> getChildren(size_t);

};

class IEventDbManager {
public:
	virtual const Event& get(size_t) = 0;
	virtual size_t add(const Event&) = 0;
	virtual void update(const Event&) = 0;
	virtual void remove(size_t) = 0;

	virtual std::vector<Comment> getComments(size_t) = 0;

};

class EventDbManager {
public:
	const Event& get(size_t);
	size_t add(const Event&);
	void update(const Event&);
	void remove(size_t);

	std::vector<Comment> getComments(size_t);

};

class ICalendarDbManager {
public:
	virtual const Calendar& get(size_t) = 0;
	virtual size_t add(const Calendar&) = 0;
	virtual void update(const Calendar&) = 0;
	virtual void remove(size_t) = 0;

	virtual std::vector<Event> getEvents(size_t) = 0;

};

class CalendarDbManager : public ICalendarDbManager {
public:
	const Calendar& get(size_t) override;
	size_t add(const Calendar&) override;
	void update(const Calendar&) override;
	void remove(size_t) override;

	std::vector<Event> getEvents(size_t) override;

};

class TagDbManager {};

class INodeDbManager {
public:
	virtual const Node& get(size_t) = 0;
	virtual size_t add(const Node&) = 0;
	virtual void update(const Node&) = 0;
	virtual void remove(size_t) = 0;

	virtual std::vector<Node> getChildren(size_t) = 0;

};

class NodeDbManager : public INodeDbManager {
public:
	const Node& get(size_t) override;
	size_t add(const Node&) override;
	void update(const Node&) override;
	void remove(size_t) override;

	std::vector<Node> getChildren(size_t) override;

};

