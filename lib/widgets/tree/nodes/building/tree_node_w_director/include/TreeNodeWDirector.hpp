#pragma once

#include <memory>

#include "ITreeNode.hpp"
#include "ITreeNodeWAnalyst.hpp"
#include "Node.hpp"

class TreeNodeW;

class TreeNodeWDirector {
  public:
    TreeNodeWDirector();

    std::unique_ptr<TreeNodeW> fillNode(TreeNodeWConvertedData data);
};
