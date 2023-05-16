#include "tree_node_subscriptions_dir_w.hpp"

#include <memory>

#include "Managers.hpp"
#include "Wt/WContainerWidget.h"
#include "Wt/WIconPair.h"
#include "Wt/WText.h"
#include "tree_node_calendar_w.hpp"
#include "tree_node_dir_w.hpp"
#include "tree_node_w.hpp"

TreeNodeSubscriptionsDirW::TreeNodeSubscriptionsDirW(std::string label, TreeNode* node) : TreeNodeDirW(label, node) {}

std::unique_ptr<TreeNodeW> TreeNodeSubscriptionsDirW::makeTreeNodeWidget(TreeNode* node) {
    std::unique_ptr<TreeNodeW> res;
    NodeType node_type = node->getNode().type;
    std::vector<std::string> tags;
    tags.push_back("tag1");
    tags.push_back("tag2");
    if (node_type & PUBLIC_CALENDAR) {
        Calendar child = Managers::instance().calendar_manager->get(node->getNode().resource_id);
        res = std::make_unique<TreeNodeCalendarW>(child.name, node);
        res.get()->addToolTip(child.description, tags, Managers::instance().user_manager->get(child.owner_id));
    } else if (node_type & PUBLIC_DIRECTORY) {
        Directory child = Managers::instance().directory_manager->get(node->getNode().resource_id);
        res = std::make_unique<TreeNodeSubscriptionsDirW>(child.name, node);
        res.get()->addToolTip(child.description, tags, Managers::instance().user_manager->get(child.owner_id));
    }
    res.get()->endNode()->addParent(this);
}
