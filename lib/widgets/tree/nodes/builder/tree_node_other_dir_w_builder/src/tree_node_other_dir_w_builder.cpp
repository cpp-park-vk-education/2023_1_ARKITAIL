#include "tree_node_other_dir_w_builder.hpp"

#include <memory>

#include "ITreeNode.hpp"
#include "tree_node_other_dir_w.hpp"
#include "tree_node_w.hpp"
#include "tree_node_w_builder_base.hpp"

TreeNodeOtherDirWBuilder::TreeNodeOtherDirWBuilder() {}

TreeNodeOtherDirWBuilder* TreeNodeOtherDirWBuilder::createTreeNodeW(ITreeNode* node) {
    tree_node_w = std::make_unique<TreeNodeOtherDirW>(node);
    return this;
}

std::unique_ptr<TreeNodeW> TreeNodeOtherDirWBuilder::getTreeNodeW() {
    std::unique_ptr<TreeNodeW> tmp = std::make_unique<TreeNodeOtherDirW>(node_);
    tree_node_w.swap(tmp);
    return tmp;
}
