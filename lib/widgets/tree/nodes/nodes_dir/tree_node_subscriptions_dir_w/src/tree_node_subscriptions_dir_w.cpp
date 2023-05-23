#include "tree_node_subscriptions_dir_w.hpp"

#include <memory>

#include "Managers.hpp"
#include "SessionScopeMap.hpp"
#include "Wt/WContainerWidget.h"
#include "Wt/WIconPair.h"
#include "Wt/WText.h"
#include "options_w_builder.hpp"
#include "options_w_director.hpp"
#include "tree_node_dir_w.hpp"
#include "tree_node_leaf_w.hpp"
#include "tree_node_w.hpp"
#include "tree_node_w_builder.hpp"
#include "tree_node_w_director.hpp"

TreeNodeSubscriptionsDirW::TreeNodeSubscriptionsDirW() {}

TreeNodeSubscriptionsDirW::TreeNodeSubscriptionsDirW(ITreeNode* node) :
    TreeNodeDirW(node) {}

std::unique_ptr<TreeNodeW> TreeNodeSubscriptionsDirW::makeTreeNodeWidget(ITreeNode* tree_node) {
    auto data = TreeNodeWAnalyst().analyseTreeNodeSubscriptionDirWChild(tree_node);
    std::unique_ptr<TreeNodeW> tree_node_w;
    if (data.components_set & Components::TYPE_SUB_DIR) {
        tree_node_w = std::make_unique<TreeNodeSubscriptionsDirW>(data.tree_node);
    } else {
        tree_node_w = std::make_unique<TreeNodeLeafW>(data.tree_node);
    }

    auto node_builder = TreeNodeWBuilder(std::move(tree_node_w));

    return TreeNodeWDirector().fillNode(data, node_builder);
}
