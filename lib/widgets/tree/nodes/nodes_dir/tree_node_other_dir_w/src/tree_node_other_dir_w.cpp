#include "tree_node_other_dir_w.hpp"

#include <memory>

#include "Managers.hpp"
#include "SessionScopeMap.hpp"
#include "Wt/WContainerWidget.h"
#include "Wt/WIconPair.h"
#include "Wt/WText.h"
#include "options_w.hpp"
#include "options_w_builder.hpp"
#include "options_w_director.hpp"
#include "tree_node_leaf_w.hpp"
#include "tree_node_w.hpp"
#include "tree_node_w_builder.hpp"
#include "tree_node_w_director.hpp"

TreeNodeOtherDirW::TreeNodeOtherDirW() {}

TreeNodeOtherDirW::TreeNodeOtherDirW(ITreeNode* node) :
    TreeNodeDirW(node) {}

std::unique_ptr<TreeNodeW> TreeNodeOtherDirW::makeTreeNodeWidget(ITreeNode* tree_node) {
    auto data = TreeNodeWAnalyst().analyseTreeNodeSubscriptionDirWChild(tree_node);
    std::unique_ptr<TreeNodeW> tree_node_w;

    if (data.components_set & Components::TYPE_OTHER_DIR) {
        tree_node_w = std::make_unique<TreeNodeOtherDirW>(data.tree_node);
    } else {
        tree_node_w = std::make_unique<TreeNodeLeafW>(data.tree_node);
    }

    auto node_builder = TreeNodeWBuilder(std::move(tree_node_w));

    return TreeNodeWDirector().fillNode(data, node_builder);
}
