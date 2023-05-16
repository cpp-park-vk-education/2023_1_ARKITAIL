#include "tree_node_subscriptions_dir_w.hpp"

#include <memory>

#include "Wt/WContainerWidget.h"
#include "Wt/WIconPair.h"
#include "Wt/WText.h"
#include "tree_node_calendar_w.hpp"
#include "tree_node_dir_w.hpp"
#include "tree_node_w.hpp"

TreeNodeSubscriptionsDirW::TreeNodeSubscriptionsDirW(std::string label, TreeNode* node) : TreeNodeDirW(label, node) {}

std::unique_ptr<TreeNodeW> TreeNodeSubscriptionsDirW::makeTreeNodeWidget(TreeNode* node) {
    std::unique_ptr<TreeNodeW> res;
    // node_type = node->getNode();
    NodeType node_type;
    std::string name = "";
    std::string desc = "";
    std::string author = "";
    std::vector<std::string> tags;
    if (node_type & PUBLIC_CALENDAR) {
        res = std::make_unique<TreeNodeCalendarW>(name, node);
        res.get()->addToolTip(desc, tags, author);
    } else if (node_type & PUBLIC_DIRECTORY) {
        res = std::make_unique<TreeNodeSubscriptionsDirW>(name, node);
        res.get()->addToolTip(desc, tags, author);
    }
    res.get()->endNode()->addParent(this);
}
