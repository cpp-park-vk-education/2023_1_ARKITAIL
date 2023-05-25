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

    EventSptr get(size_t event_id) override;
    size_t add(EventSptr event) override;
    void update(EventSptr event) override;
    void remove(size_t event_id) override;

    std::vector<Comment> getComments(size_t event_id) override;
    std::chrono::time_point<clock_t> parseTime(std::string str_time) override;

private:
    std::shared_ptr<IDbManagers> db_;

};

