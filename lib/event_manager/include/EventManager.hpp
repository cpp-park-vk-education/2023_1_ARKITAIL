#pragma once

#include <chrono>
#include <string>

#include "IEventManager.hpp"
#include "UnmetDeps.hpp"

class EventManager : public IEventManager {
public:
    using clock_t = std::chrono::steady_clock;

	const Event& get(size_t event_id) override;
	size_t add(const Event& event) override;
	void update(const Event& event) override;
	void remove(size_t event_id) override;

	std::vector<Comment> getComments(size_t event_id) override;
	std::chrono::time_point<clock_t> parseTime(std::string str_time) override;

private:
    IEventDbManager* manager_;

};

