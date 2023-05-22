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

    const Event& get(int);
    int add(const Event&);
    void update(const Event&);
    void remove(int);

    std::vector<Comment> getComments(int);
    
private:
    std::shared_ptr<DbMock> db_;
    int aid_;

};

