#pragma once

#include <vector>

#include "Event.hpp"
#include "Comment.hpp"

class IEventDbManager {
public:
    virtual EventSptr get(int event_id) = 0;
    virtual int add(EventSptr) = 0;
    virtual void update(EventSptr) = 0;
    virtual void remove(int event_id) = 0;

};


