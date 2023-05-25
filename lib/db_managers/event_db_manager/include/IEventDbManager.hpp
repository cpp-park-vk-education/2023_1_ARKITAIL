#pragma once

#include <vector>

#include "Event.hpp"
#include "Comment.hpp"

class IEventDbManager {
public:
    virtual EventSptr get(size_t) = 0;
    virtual size_t add(EventSptr) = 0;
    virtual void update(EventSptr) = 0;
    virtual void remove(size_t) = 0;

    virtual std::vector<Comment> getComments(size_t) = 0;

};


