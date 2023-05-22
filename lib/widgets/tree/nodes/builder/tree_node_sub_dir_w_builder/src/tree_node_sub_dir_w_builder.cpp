#include "tree_node_sub_dir_w_builder.hpp"

#include <memory>

#include "ITreeNode.hpp"
#include "tree_node_subscriptions_dir_w.hpp"
#include "tree_node_w.hpp"
#include "tree_node_w_builder_base.hpp"

TreeNodeSubDirWBuilder::TreeNodeSubDirWBuilder() {}

TreeNodeSubDirWBuilder* TreeNodeSubDirWBuilder::createTreeNodeW(ITreeNode* node) {
    tree_node_w = std::make_unique<TreeNodeSubscriptionsDirW>(node);
    return this;
}

std::unique_ptr<TreeNodeW> TreeNodeSubDirWBuilder::getTreeNodeW() {
    std::unique_ptr<TreeNodeW> tmp = std::make_unique<TreeNodeSubscriptionsDirW>(node_);
    tree_node_w.swap(tmp);
    return tmp;
}
