#include "tree_node_w_analyst.hpp"

#include "Calendar.hpp"
#include "Directory.hpp"
#include "Managers.hpp"
#include "SessionScopeMap.hpp"

TreeNodeWAnalyst::TreeNodeWAnalyst() {}

TreeNodeWConvertedData TreeNodeWAnalyst::analyseTreeNodeDirWChild(ITreeNode* tree_node) {
    Node node = tree_node->getNode();
    std::vector<std::string> tags;
    // OptionsWBuilder options_builder;
    auto mgr = SessionScopeMap::instance().get()->managers();
    User user = mgr->user_manager()->get();

    if (node.type & (NodeType::PRIVATE_CALENDAR | NodeType::PUBLIC_CALENDAR)) {
        CalendarSptr child = mgr->calendar_manager()->get(node.resource_id);
        return TreeNodeWConvertedData{TreeNodeWType::PERSONAL_CALENDAR, child->summary,
                                      child->description, tags, user.nickname };
        // TreeNodeWBuilder()
        //     .createTreeNodeLeafW(tree_node)
        //     ->addHead(std::make_unique<Wt::WText>(child.name))
        //     ->addOptions(
        //         std::move(OptionsWDirector().createOptionsPersonalCalendarW(options_builder)))
        //     ->addToolTip(child.description, tags)
        //     ->addParent(this)
        //     ->endNode()
        //     ->getTreeNodeW();

    } else if (node.type & NodeType::PROFILE) {
        // Profile child = mgr->profile_manager()->get(node.resource_id);
        // return TreeNodeWConvertedData{TreeNodeWType::DIR, child.name, "", tags,
        //                              user.nickname};
        // return TreeNodeWBuilder()
        //     .createTreeNodeProfileW(tree_node)
        //     ->addHead(std::make_unique<InPlaceEditTitle>(child.name))
        //     ->addParent(this)
        //     ->endNode()
        //     ->getTreeNodeW();
    } else if (node.type & (NodeType::PRIVATE_DIRECTORY | NodeType::PUBLIC_DIRECTORY)) {
        Directory child = mgr->directory_manager()->get(node.resource_id);
        return TreeNodeWConvertedData{TreeNodeWType::DIR, child.name, child.description, tags,
                                      user.nickname};
        // TreeNodeWBuilder()
        //     .createTreeNodeDirW(tree_node)
        //     ->addHead(std::make_unique<Wt::WText>(child.name))
        //     ->addOptions(std::move(OptionsWDirector().createOptionsCalendarsDirW(options_builder)))
        //     ->addToolTip(child.description, tags)
        //     ->addParent(this)
        //     ->endNode()
        //     ->getTreeNodeW();

    } else if (node.type & (NodeType::ROOT | NodeType::PRIVATE_GROUP | NodeType::PUBLIC_GROUP)) {
        Directory child = mgr->directory_manager()->get(node.resource_id);
        return TreeNodeWConvertedData();
        // TreeNodeWBuilder()
        //     .createTreeNodeDirW(tree_node)
        //     ->addHead(std::make_unique<Wt::WText>(child.name))
        //     ->addParent(this)
        //     ->endNode()
        //     ->getTreeNodeW();

    } else if (node.type & (NodeType::PROFILE_GROUP)) {
        Directory child = mgr->directory_manager()->get(node.resource_id);
        return TreeNodeWConvertedData();
        // TreeNodeWBuilder()
        //     .createTreeNodeDirW(tree_node)
        //     ->addHead(std::make_unique<Wt::WText>(child.name))
        //     ->addParent(this)
        //     ->endNode()
        //     ->getTreeNodeW();

    } else if (node.type & NodeType::SUBSCRIPTIONS_GROUP) {
        Directory child = mgr->directory_manager()->get(node.resource_id);
        return TreeNodeWConvertedData();
        // TreeNodeWBuilder()
        //     .createTreeNodeSubscriptionsDirW(tree_node)
        //     ->addHead(std::make_unique<Wt::WText>(child.name))
        //     ->addParent(this)
        //     ->endNode()
        //     ->getTreeNodeW();
    }
}

TreeNodeWConvertedData TreeNodeWAnalyst::analyseTreeNodeOtherDirWChild(ITreeNode* tree_node) {}

TreeNodeWConvertedData TreeNodeWAnalyst::analyseTreeNodeSubscriptionDirWChild(
    ITreeNode* tree_node) {}
