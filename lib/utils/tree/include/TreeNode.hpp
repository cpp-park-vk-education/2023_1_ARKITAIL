#pragma once

#include <vector>
#include <memory>

#include "Node.hpp"
#include "ITreeNode.hpp"

class TreeNode : public ITreeNode {
public:
    TreeNode(NodeSptr node);
    TreeNode(NodeSptr node, ITreeNode* parent);

    const Node& getNode() override;
    ITreeNode* getParent() override;

    std::vector<ITreeNode*> getChildren() override;
    ITreeNode* addChild(NodeSptr node) override;
    std::unique_ptr<ITreeNode> remove() override;

    bool isChecked() override;

    void check() override;
    void uncheck() override;

private:
    std::unique_ptr<ITreeNode> removeChild(ITreeNode* child) override;

    NodeSptr node_;
    ITreeNode* parent_;
    std::vector<std::unique_ptr<ITreeNode>> children_;
    bool checked_;

};

