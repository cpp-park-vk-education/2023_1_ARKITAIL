#include "tree_node_w_analyst.hpp"

#include "Calendar.hpp"
#include "Directory.hpp"
#include "Managers.hpp"
#include "SessionScopeMap.hpp"
#include "User.hpp"

TreeNodeWAnalyst::TreeNodeWAnalyst() {}

TreeNodeWConvertedData TreeNodeWAnalyst::analyseTreeNodeDirWChild(ITreeNode* tree_node) {
    Node node = tree_node->getNode();
    std::vector<std::string> tags;
    auto mgr = SessionScopeMap::instance().get()->managers();
    User user = mgr->user_manager()->get();

    if ((tree_node->getParent()->getNode().type & NodeType::SUBSCRIPTIONS_GROUP)) {
        // нужна проверка на sub/unsub
        if (node.type & NodeType::PUBLIC_DIRECTORY) {
            Directory child = mgr->directory_manager()->get(node.resource_id);
            return TreeNodeWConvertedData{
                TreeNodeWType::SUB_DIR_OPTIONS,           child.name, child.description, tags,
                mgr->user_manager()->get(child.owner_id), tree_node};

        } else {
            Calendar child = mgr->calendar_manager()->get(node.resource_id);
            return TreeNodeWConvertedData{
                TreeNodeWType::SUB_CALENDAR_OPTIONS,      child.name, child.description, tags,
                mgr->user_manager()->get(child.owner_id), tree_node};
        }

    } else if (node.type & (NodeType::PRIVATE_CALENDAR | NodeType::PUBLIC_CALENDAR)) {
        Calendar child = mgr->calendar_manager()->get(node.resource_id);
        return TreeNodeWConvertedData{
            TreeNodeWType::PERSONAL_CALENDAR,         child.name, child.description, tags,
            mgr->user_manager()->get(child.owner_id), tree_node};

    } else if (node.type & (NodeType::PRIVATE_DIRECTORY | NodeType::PUBLIC_DIRECTORY)) {
        Directory child = mgr->directory_manager()->get(node.resource_id);
        return TreeNodeWConvertedData{TreeNodeWType::DIR,
                                      child.name,
                                      child.description,
                                      tags,
                                      mgr->user_manager()->get(child.owner_id),
                                      tree_node};

    } else if (node.type & (NodeType::ROOT | NodeType::PRIVATE_GROUP | NodeType::PUBLIC_GROUP |
                            NodeType::SUBSCRIPTIONS_GROUP | NodeType::PROFILE_GROUP)) {
        Directory child = mgr->directory_manager()->get(node.resource_id);
        return TreeNodeWConvertedData{TreeNodeWType::GROUP,
                                      child.name,
                                      child.description,
                                      tags,
                                      mgr->user_manager()->get(child.owner_id),
                                      tree_node};

    } else if (node.type & NodeType::PROFILE) {
        // Profile child = Managers::instance().profile_manager->get(node.resource_id);
        // return TreeNodeWConvertedData{TreeNodeWType::PROFILE_LEAF, child.name, child.description,
        //                               tags, mgr->user_manager()->get(child.owner_id)};
    }
}

TreeNodeWConvertedData TreeNodeWAnalyst::analyseTreeNodeOtherDirWChild(ITreeNode* tree_node) {
    Node node = tree_node->getNode();
    std::vector<std::string> tags;
    auto mgr = SessionScopeMap::instance().get()->managers();
    User user = mgr->user_manager()->get();
}

TreeNodeWConvertedData TreeNodeWAnalyst::analyseTreeNodeSubscriptionDirWChild(
    ITreeNode* tree_node) {
    Node node = tree_node->getNode();
    std::vector<std::string> tags;
    auto mgr = SessionScopeMap::instance().get()->managers();
    User user = mgr->user_manager()->get();
}
