#pragma once

#include <memory>
#include <vector>

#include "Node.hpp"

class ITreeNode {
public:
    virtual const Node& getNode() = 0;
    virtual ITreeNode* getParent() = 0;

    virtual std::vector<ITreeNode*> getChildren() = 0;
    virtual ITreeNode* addChild(const Node& node) = 0;
    virtual std::unique_ptr<ITreeNode> remove() = 0;

    virtual bool isChecked() = 0;

    virtual void check() = 0;
    virtual void uncheck() = 0;

    virtual std::unique_ptr<ITreeNode> removeChild(ITreeNode* child) = 0;

};

