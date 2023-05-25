#pragma once

#include <mutex>
#include <thread>
#include <memory>
#include <unordered_map>

#include "SessionScope.hpp"

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

