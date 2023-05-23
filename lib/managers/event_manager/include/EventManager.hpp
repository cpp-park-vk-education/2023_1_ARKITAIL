#pragma once

#include <chrono>
#include <memory>
#include <string>

#include "IDbManagers.hpp"
#include "IEventManager.hpp"
#include "UnmetDeps.hpp"

class EventManager : public IEventManager {
public:
    using clock_t = std::chrono::steady_clock;

    EventManager(std::shared_ptr<IDbManagers> db);

    const Event& get(int event_id) override;
    int add(const Event& event) override;
    void update(const Event& event) override;
    void remove(int event_id) override;

    //std::vector<Comment> getComments(int event_id) override;
    std::chrono::time_point<clock_t> parseTime(std::string str_time) override;

private:
	std::shared_ptr<IDbManagers> db_;

};
