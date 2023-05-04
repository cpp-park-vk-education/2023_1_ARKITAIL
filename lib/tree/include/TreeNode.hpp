#pragma once

#include <vector>

#include "Node.hpp"

class TreeNode {
public:
    TreeNode(const Node& node);
    const Node& getNode();
    const std::vector<TreeNode*>& getChilds();
    void check();

private:
    Node node;
    std::vector<TreeNode*> childs;
    bool checked;
};

