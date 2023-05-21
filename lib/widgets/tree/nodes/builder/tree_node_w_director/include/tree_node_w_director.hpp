#pragma once

#include <memory>

#include "ITreeNode.hpp"
#include "Node.hpp"
#include "tree_node_w.hpp"
#include "tree_node_w_analyst.hpp"
#include "tree_node_w_builder_base.hpp"

class TreeNodeW;

class TreeNodeWDirector {
  public:
    TreeNodeWDirector();

    std::unique_ptr<TreeNodeW> createNode(TreeNodeWConvertedData data);

  private:
    std::unique_ptr<TreeNodeWBuilderBase> node_builder;
};
