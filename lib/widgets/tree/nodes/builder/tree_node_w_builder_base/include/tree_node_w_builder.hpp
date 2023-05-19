#pragma once

#include <memory>

#include "ITreeNode.hpp"
#include "User.hpp"
#include "options_w.hpp"

class TreeNodeW;

class TreeNodeWBuilderBase {
  public:
    TreeNodeWBuilderBase();
    TreeNodeWBuilderBase();
    virtual TreeNodeWBuilderBase* createTreeNodeW(ITreeNode* node, TreeNodeW* this_node,
                                                  TreeNodeW* parant_node) = 0;

    virtual TreeNodeWBuilderBase* addHead();
    virtual TreeNodeWBuilderBase* addCheckBox();
    virtual TreeNodeWBuilderBase* addOptions();
    virtual TreeNodeWBuilderBase* addToolTip();
    virtual TreeNodeWBuilderBase* addToolTip();
    virtual TreeNodeWBuilderBase* addParent();
    virtual TreeNodeWBuilderBase* endNode();

    std::unique_ptr<TreeNodeW> getTreeNodeW() {
        return
    }

  protected:
    tree_node_w
};
