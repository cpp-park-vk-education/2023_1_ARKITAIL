#pragma once

#include <memory>
#include <string>

#include "IDbManagers.hpp"
#include "IEventManager.hpp"

class EventManager : public IEventManager {
public:
    EventManager(std::shared_ptr<IDbManagers> db);

    EventSptr get(int event_id) override;
    int add(EventSptr event) override;
    void update(EventSptr event) override;
    void remove(int event_id) override;

private:
    std::shared_ptr<IDbManagers> db_;

};

