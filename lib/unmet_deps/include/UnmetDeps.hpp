#pragma once

#include <vector>

#include "Node.hpp"
#include "Directory.hpp"

class Session {};
class NavbarW {};

class DBConnection {};

class UserDbManager {};

class IDirectoryDbManager {
public:
	virtual const Directory& get(size_t) = 0;
	virtual size_t add(const Directory&) = 0;
	virtual size_t update(const Directory&) = 0;
	virtual void remove(size_t) = 0;

	virtual std::vector<Directory> getChildren() = 0;

};

class DirectoryDbManager : public IDirectoryDbManager {
public:
	const Directory& get(size_t directory_id) override;
	size_t add(const Directory& directory) override;
	size_t update(const Directory& directory) override;
	void remove(size_t directory_id) override;
	
	std::vector<Directory> getChildren(size_t directory_id);

};

class EventDbManager {};

class CalendarDbManager {};

class TagDbManager {};

class INodeDbManager {
public:
	virtual const Node& get(size_t) = 0;
	virtual size_t add(const Node&) = 0;
	virtual size_t update(const Node&) = 0;
	virtual void remove(size_t) = 0;

	virtual std::vector<Node> getChildren(size_t) = 0;

};

class NodeDbManager : public INodeDbManager {
public:
	const Node& get(size_t node_id) override;
	size_t add(const Node& node) override;
	size_t update(const Node& node) override;
	void remove(size_t node_id) override;

	std::vector<Node> getChildren(size_t node_id) override;

};

