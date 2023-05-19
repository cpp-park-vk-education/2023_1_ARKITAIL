#pragma once

#include <vector>

#include "Node.hpp"
#include "INodeDbManager.hpp"

class NodeDbManagerMock : public INodeDbManager {
public:
    NodeDbManagerMock();

    const Node& get(size_t node_id);
    size_t add(const Node& node);
    void update(const Node& node);
    void remove(size_t node_id);

    std::vector<Node> getChildren(size_t node_id);

private:
    std::vector<Node> data_;
    size_t aid_;

};

