#include "TreeNodeLeafWBuilder.hpp"

#include <memory>

#include "ITreeNode.hpp"
#include "TreeNodeLeafW.hpp"
#include "TreeNodeW.hpp"
#include "TreeNodeWBuilderBase.hpp"

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
