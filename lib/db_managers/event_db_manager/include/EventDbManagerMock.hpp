#pragma once 

#include <vector>

#include "IEventDbManager.hpp"
#include "Comment.hpp"
#include "Event.hpp"

class EventDbManagerMock : public IEventDbManager {
public:
    EventDbManagerMock();

    const Event& get(size_t);
    size_t add(const Event&);
    void update(const Event&);
    void remove(size_t);

    std::vector<Comment> getComments(size_t);
    std::vector<Event> getByCalendar(size_t calendar_id);  // mock assistance
    
private:
    std::vector<Event> data_;
    size_t aid_;

};

