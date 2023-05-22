#pragma once

#include <vector>
#include <memory>

#include "Node.hpp"
#include "ITreeNode.hpp"

class TreeNode : public ITreeNode {
public:
    TreeNode(const Node& node, ITreeNode* parent);

    const Node& getNode() override;
    ITreeNode* getParent() override;

    std::vector<ITreeNode*> getChildren() override;
    ITreeNode* addChild(const Node& node) override;
    std::unique_ptr<ITreeNode> remove() override;

    bool isChecked() override;

    void check() override;
    void uncheck() override;

private:
    std::unique_ptr<ITreeNode> removeChild(ITreeNode* child) override;

    Node node_;
    ITreeNode* parent_;
    std::vector<std::unique_ptr<ITreeNode>> children_;
    bool checked_;

};

