#pragma once

#include <cstddef>

#include "Event.hpp"
#include "TreeNode.hpp"

class Tree {
public:
    Tree(const Node& node);

    TreeNode* insertNode(const TreeNode& node, TreeNode* parent);
    void removeNode(TreeNode* node);
    TreeNode* getRoot();
    std::vector<TreeNode*> getChilds(TreeNode* node);
    std::vector<Event> getCheckedEvents();
    std::vector<Event> checkNode();
    size_t checked();
    bool someChecked();

private:
    TreeNode root;
    size_t checked_count;
    
};

