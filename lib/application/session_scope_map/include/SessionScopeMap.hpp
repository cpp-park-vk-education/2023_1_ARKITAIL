#pragma once

#include <mutex>
#include <string>
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

	void add(std::string);

	std::unordered_map<std::string, std::unique_ptr<SessionScope>> container_;
	std::mutex container_mutex_;

};

