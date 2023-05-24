#include "TreeNodeLeafWBuilder.hpp"

#include <memory>

#include "ITreeNode.hpp"
#include "TreeNodeWBuilderBase.hpp"
#include "tree_node_leaf_w.hpp"
#include "tree_node_w.hpp"

TreeNodeLeafWBuilder::TreeNodeLeafWBuilder() {}

TreeNodeLeafWBuilder* TreeNodeLeafWBuilder::createTreeNodeW(ITreeNode* node) {
    tree_node_w = std::make_unique<TreeNodeLeafW>(node);
    return this;
}

std::unique_ptr<TreeNodeW> TreeNodeLeafWBuilder::getTreeNodeW() {
    std::unique_ptr<TreeNodeW> tmp = std::make_unique<TreeNodeLeafW>(node_);
    tmp.swap(tree_node_w);
    return tmp;
}
