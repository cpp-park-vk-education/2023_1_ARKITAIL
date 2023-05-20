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

    const Event& get(size_t);
    size_t add(const Event&);
    void update(const Event&);
    void remove(size_t);

    std::vector<Comment> getComments(size_t);
    
private:
    std::shared_ptr<DbMock> db_;
    size_t aid_;

};

