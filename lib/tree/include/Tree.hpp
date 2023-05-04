#pragma once

#include <cstddef>

#include "Event.hpp"
#include "TreeNode.hpp"

class Tree {
public:
    Tree(const Node& node);
    const TreeNode& insertNode(const TreeNode& node, const TreeNode& parent);
    void removeNode(const TreeNode& node);
    const TreeNode& getRoot();
    const std::vector<TreeNode*> getChilds(const TreeNode& node);
    std::vector<Event> getCheckedEvents();
    std::vector<Event> checkNode();
    size_t checked();
    bool someChecked();

private:
    TreeNode root;
    size_t checked_count;
    
};

