#pragma once

#include <vector>
#include <memory>

#include "DbMock.hpp"
#include "Node.hpp"
#include "INodeDbManager.hpp"

class NodeDbManagerMock : public INodeDbManager {
public:
    NodeDbManagerMock(std::shared_ptr<DbMock> db);

    const Node& get(size_t node_id);
    size_t add(const Node& node);
    void update(const Node& node);
    void remove(size_t node_id);

    std::vector<Node> getChildren(size_t node_id);

private:
    std::shared_ptr<DbMock> db_;
    size_t aid_;

};

