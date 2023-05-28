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

    EventSptr get(int event_id) override;
    int add(EventSptr) override;
    void update(EventSptr) override;
    void remove(int event_id) override;

    //std::vector<Comment> getComments(int event_id);
    
private:
    std::shared_ptr<DbMock> db_;
    int aid_;

};

