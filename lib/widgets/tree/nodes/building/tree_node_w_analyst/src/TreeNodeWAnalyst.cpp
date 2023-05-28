#include "TreeNodeWAnalyst.hpp"

#include <memory>

#include "Calendar.hpp"
#include "Directory.hpp"
#include "Managers.hpp"
#include "Node.hpp"
#include "SessionScopeMap.hpp"
#include "Tag.hpp"
#include "User.hpp"

TreeNodeWAnalyst::TreeNodeWAnalyst() {}

TreeNodeWConvertedData TreeNodeWAnalyst::analyseTreeNodeWChild(ITreeNode* tree_node) {
    Node node = tree_node->getNode();
    std::vector<std::string> tags;
    auto mgr = SessionScopeMap::instance().get()->managers();
    UserSptr user = mgr->user_manager()->get();
    TreeNodeWConvertedData data;
    if (!(node.type & NodeType::ROOT) &&
        (tree_node->getParent()->getNode().type & NodeType::SUBSCRIPTIONS_GROUP)) {
        // тут только unsub, так как это подписки
        if (node.type & NodeType::PUBLIC_DIRECTORY) {
            DirectorySptr child = mgr->directory_manager()->get(node.resource_id);
            data = TreeNodeWConvertedData{
                TreeNodeWType::SUB_DIR_OPTIONS,           child->name, child->description, tags,
                *mgr->user_manager()->get(child->owner_id), tree_node};

        } else {
            CalendarSptr child = mgr->calendar_manager()->get(node.resource_id);
            data = TreeNodeWConvertedData{
                TreeNodeWType::SUB_CALENDAR_OPTIONS,      child->summary, child->description, tags,
                *mgr->user_manager()->get(child->owner_id), tree_node};
        }

    } else if (node.type & (NodeType::PRIVATE_CALENDAR | NodeType::PUBLIC_CALENDAR)) {
        CalendarSptr child = mgr->calendar_manager()->get(node.resource_id);

        data = TreeNodeWConvertedData{
            TreeNodeWType::PERSONAL_CALENDAR,         child->summary, child->description, tags,
            *mgr->user_manager()->get(child->owner_id), tree_node};

    } else if (node.type & (NodeType::PRIVATE_DIRECTORY | NodeType::PUBLIC_DIRECTORY)) {
        DirectorySptr child = mgr->directory_manager()->get(node.resource_id);

        data = TreeNodeWConvertedData{TreeNodeWType::DIR,
                                      child->name,
                                      child->description,
                                      tags,
                                      *mgr->user_manager()->get(child->owner_id),
                                      tree_node};

    } else if (node.type & (NodeType::ROOT | NodeType::PRIVATE_GROUP | NodeType::PUBLIC_GROUP |
                            NodeType::SUBSCRIPTIONS_GROUP | NodeType::PROFILE_GROUP)) {
        DirectorySptr child = mgr->directory_manager()->get(node.resource_id);

        data = TreeNodeWConvertedData{TreeNodeWType::GROUP,
                                      child->name,
                                      child->description,
                                      tags,
                                      *mgr->user_manager()->get(child->owner_id),
                                      tree_node};

    } else if (node.type & NodeType::PROFILE) {
        // Profile child = Managers::instance().profile_manager->get(node.resource_id);
        // return TreeNodeWConvertedData{TreeNodeWType::PROFILE_LEAF, child.name, child.description,
        //                               tags, mgr->user_manager()->get(child.owner_id)};
    }
    return data;
}
