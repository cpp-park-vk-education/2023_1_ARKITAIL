#pragma once

#include <vector>

#include "Event.hpp"
#include "Comment.hpp"

class IEventDbManager {
public:
    virtual const Event& get(int) = 0;
    virtual int add(const Event&) = 0;
    virtual void update(const Event&) = 0;
    virtual void remove(int) = 0;

    virtual std::vector<Comment> getComments(int) = 0;

};


