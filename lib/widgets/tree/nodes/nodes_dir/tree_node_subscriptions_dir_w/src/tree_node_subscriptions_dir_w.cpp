#include "tree_node_subscriptions_dir_w.hpp"

#include <memory>

#include "Managers.hpp"
#include "Wt/WContainerWidget.h"
#include "Wt/WIconPair.h"
#include "Wt/WText.h"
#include "options_w_builder.hpp"
#include "options_w_director.hpp"
#include "tree_node_dir_w.hpp"
#include "tree_node_leaf_w.hpp"
#include "tree_node_w.hpp"
#include "tree_node_w_builder.hpp"

TreeNodeSubscriptionsDirW::TreeNodeSubscriptionsDirW(ITreeNode* node) :
    TreeNodeDirW(node) {}

std::unique_ptr<TreeNodeW> TreeNodeSubscriptionsDirW::makeTreeNodeWidget(ITreeNode* node) {
    NodeType node_type = node->getNode().type;
    std::vector<std::string> tags;
    tags.push_back("tag1");
    tags.push_back("tag2");
    OptionsWBuilder options_builder;

    if (node_type & NodeType::PUBLIC_CALENDAR) {
        Calendar child = Managers::instance().calendar_manager->get(node->getNode().resource_id);
        return TreeNodeWBuilder()
            .createTreeNodeLeafW(node)
            ->addHead(std::make_unique<Wt::WText>(child.name))
            ->addOptions(
                std::move(OptionsWDirector().createOptionsUnsubscriptionW(options_builder)))
            ->addToolTip(child.description, tags,
                         Managers::instance().user_manager->get(child.owner_id))
            ->addParent(this)
            ->endNode()
            ->getTreeNodeW();

    } else if (node_type & NodeType::PUBLIC_DIRECTORY) {
        Directory child = Managers::instance().directory_manager->get(node->getNode().resource_id);
        return TreeNodeWBuilder()
            .createTreeNodeSubscriptionsDirW(node)
            ->addHead(std::make_unique<Wt::WText>(child.name))
            ->addOptions(
                std::move(OptionsWDirector().createOptionsUnsubscriptionW(options_builder)))
            ->addToolTip(child.description, tags,
                         Managers::instance().user_manager->get(child.owner_id))
            ->addParent(this)
            ->endNode()
            ->getTreeNodeW();
    }
}
