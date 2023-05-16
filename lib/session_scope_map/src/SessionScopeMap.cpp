#include <mutex>
#include <thread>
#include <utility>

#include "SessionScopeMap.hpp"
#include "SessionScope.hpp"

SessionScopeMap::SessionScopeMap() {}

SessionScopeMap& SessionScopeMap::instance() {
	static SessionScopeMap ssm;
	return ssm;
}

SessionScope* SessionScopeMap::get(std::thread::id tid) {
	std::lock_guard<std::mutex> lg(container_mutex_);
	return container_[tid].get();
}

void SessionScopeMap::add(std::thread::id tid) {
	std::lock_guard<std::mutex> lg(container_mutex_);
	if (container_.find(tid) != container_.end())
		return;

	container_.insert(std::make_pair(tid, std::make_unique<SessionScope>()));
}

void SessionScopeMap::remove(std::thread::id tid) {
	std::lock_guard<std::mutex> lg(container_mutex_);
	container_.erase(tid);
}

