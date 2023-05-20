#pragma once

#include "SessionScope.hpp"
#include <mutex>
#include <thread>
#include <memory>

class SessionScopeMap {
public:
	static SessionScopeMap& instance();

	SessionScope* get();
	void remove();

private:
	SessionScopeMap();

	void add(std::thread::id);

	std::unordered_map<std::thread::id, std::unique_ptr<SessionScope>> container_;
	std::mutex container_mutex_;

};

