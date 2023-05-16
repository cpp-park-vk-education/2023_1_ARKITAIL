#pragma once

#include <cstddef>

#include "Event.hpp"
#include "TreeNode.hpp"

class Tree {
public:
    Tree(const Node& node);

    TreeNode* getRoot();

    std::vector<Event> getCheckedEvents();

    std::vector<Event> checkNode(TreeNode* node);
    void uncheckNode(TreeNode* node);

    size_t checked();

private:
    std::unique_ptr<TreeNode> root_;
    size_t checked_;
    
};

