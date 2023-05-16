#pragma once

#include <vector>
#include <memory>

#include "Node.hpp"

class TreeNode {
public:
    TreeNode(const Node& node, TreeNode* parent);

    const Node& getNode();
    TreeNode* getParent();

    std::vector<TreeNode*> getChildren();
    TreeNode* addChild(const Node& node);
    std::unique_ptr<TreeNode> remove();

    bool isChecked();

    void check();
    void uncheck();

private:
    std::unique_ptr<TreeNode> removeChild(TreeNode* child);

    const Node& node_;
    TreeNode* parent_;
    std::vector<std::unique_ptr<TreeNode>> children_;
    bool checked_;

};

