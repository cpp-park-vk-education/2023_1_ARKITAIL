#include "TreeNodeDirWBuilder.hpp"

#include <memory>

#include "ITreeNode.hpp"
#include "tree_node_dir_w.hpp"
#include "tree_node_w.hpp"

TreeNodeDirWBuilder::TreeNodeDirWBuilder() {}

TreeNodeDirWBuilder* TreeNodeDirWBuilder::createTreeNodeW(ITreeNode* node) {
    tree_node_w = std::make_unique<TreeNodeDirW>(node);
    return this;
}

std::unique_ptr<TreeNodeW> TreeNodeDirWBuilder::getTreeNodeW() {
    std::unique_ptr<TreeNodeW> tmp = std::make_unique<TreeNodeDirW>(node_);
    tmp.swap(tree_node_w);
    return tmp;
}
