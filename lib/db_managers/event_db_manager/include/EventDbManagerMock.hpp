#pragma once 

#include <vector>
#include <memory>

#include "DbMock.hpp"
#include "IEventDbManager.hpp"
#include "Comment.hpp"
#include "Event.hpp"

class EventDbManagerMock : public IEventDbManager {
public:
    EventDbManagerMock(std::shared_ptr<DbMock> db);

    const Event& get(int event_id);
    int add(const Event&);
    void update(const Event&);
    void remove(int event_id);

    //std::vector<Comment> getComments(int event_id);
    
private:
    std::shared_ptr<DbMock> db_;
    int aid_;

};

