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
#include "tree_node_sub_dir_w_builder.hpp"
#include "tree_node_w.hpp"
#include "tree_node_w_builder_base.hpp"

TreeNodeSubscriptionsDirW::TreeNodeSubscriptionsDirW(ITreeNode* node) :
    TreeNodeDirW(node) {}

std::unique_ptr<TreeNodeW> TreeNodeSubscriptionsDirW::makeTreeNodeWidget(ITreeNode* tree_node) {
    auto mgr = SessionScopeMap::instance().get()->managers();
    std::unique_ptr<TreeNodeW> res;

    NodeType node_type = tree_node->getNode().type;
    std::vector<std::string> tags;
    tags.push_back("tag1");
    tags.push_back("tag2");
    OptionsWBuilder options_builder;

    if (node_type & NodeType::PUBLIC_CALENDAR) {
        Calendar child = mgr->calendar_manager()->get(tree_node->getNode().resource_id);
        res = std::make_unique<TreeNodeLeafW>(tree_node);
        res.get()
            ->addCheckBox()
            ->addHead(std::make_unique<Wt::WText>(child.name))
            ->addToolTip(child.description, tags, mgr->user_manager()->get(child.owner_id))
            ->endNode();
        // return TreeNodeLeafWBuilder()
        //     .createTreeNodeW(node)
        //     ->addHead(std::make_unique<Wt::WText>(child.name))
        //     ->addOptions(OptionsWDirector().createOptionsUnsubscriptionW(options_builder))
        //     ->addToolTip(child.description, tags, mgr->user_manager()->get(child.owner_id))
        //     ->addParent(this)
        //     ->endNode()
        //     ->getTreeNodeW();

    } else if (node_type & NodeType::PUBLIC_DIRECTORY) {
        Directory child = mgr->directory_manager()->get(tree_node->getNode().resource_id);
        res = std::make_unique<TreeNodeSubscriptionsDirW>(tree_node);
        res.get()
            ->addCheckBox()
            ->addHead(std::make_unique<Wt::WText>(child.name))
            // ->addToolTip(child.description, tags, mgr->user_manager()->get(child.owner_id))
            ->endNode();
        // return TreeNodeSubDirWBuilder()
        //     .createTreeNodeW(node)
        //     ->addHead(std::make_unique<Wt::WText>(child.name))
        //     ->addOptions(OptionsWDirector().createOptionsUnsubscriptionW(options_builder))
        //     ->addToolTip(child.description, tags, mgr->user_manager()->get(child.owner_id))
        //     ->addParent(this)
        //     ->endNode()
        //     ->getTreeNodeW();
    }
    return res;
}
