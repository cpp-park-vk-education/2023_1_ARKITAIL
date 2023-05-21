#include "tree_node_dir_w_builder.hpp"

#include <memory>

#include "ITreeNode.hpp"
#include "tree_node_dir_w.hpp"
#include "tree_node_w.hpp"
#include "tree_node_w_builder_base.hpp"

TreeNodeDirWBuilder::TreeNodeDirWBuilder() {}

TreeNodeDirWBuilder* TreeNodeDirWBuilder::createTreeNodeW(ITreeNode* node) {
    tree_node_w = std::make_unique<TreeNodeDirW>(node);
    return this;
}

std::unique_ptr<TreeNodeW> TreeNodeDirWBuilder::getTreeNodeW() {
    std::unique_ptr<TreeNodeW> tmp = std::make_unique<TreeNodeDirW>(node);
    tmp.swap(tree_node_w);
    return std::move(tmp);
}
