#pragma once

#include <vector>

#include "Node.hpp"

class TreeNode {
public:
    TreeNode(const Node& node);

    const Node& getNode();
    std::vector<TreeNode*> getChilds() const;

    bool isChecked();
    void check();

private:
    Node node;
    std::vector<TreeNode*> childs;
    bool checked;
};

