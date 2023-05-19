#pragma once

#include <vector>

#include "Event.hpp"
#include "Comment.hpp"

class IEventDbManager {
public:
    virtual const Event& get(size_t) = 0;
    virtual size_t add(const Event&) = 0;
    virtual void update(const Event&) = 0;
    virtual void remove(size_t) = 0;

    virtual std::vector<Comment> getComments(size_t) = 0;
    virtual std::vector<Event> getByCalendar(size_t calendar_id) = 0;  // mock assistance
};


