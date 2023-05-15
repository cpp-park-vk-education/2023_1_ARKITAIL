#pragma once

#include <vector>

#include "Node.hpp"

class TreeNode {
public:
    TreeNode(const Node& node);

    const Node& getNode();
    std::vector<TreeNode*> getChildren() const;

    bool isChecked();
    void check();

private:
    Node node_;
    std::vector<TreeNode*> children_;
    bool checked_;
};

