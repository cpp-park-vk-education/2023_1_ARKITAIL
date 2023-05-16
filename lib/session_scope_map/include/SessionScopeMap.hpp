#pragma once

#include "SessionScope.hpp"
#include <mutex>
#include <thread>
#include <memory>

class SessionScopeMap {
public:
	static SessionScopeMap& instance();

	SessionScope* get(std::thread::id);
	void add(std::thread::id);
	void remove(std::thread::id);

private:
	SessionScopeMap();

	std::unordered_map<std::thread::id, std::unique_ptr<SessionScope>> container_;
	std::mutex container_mutex_;

};

