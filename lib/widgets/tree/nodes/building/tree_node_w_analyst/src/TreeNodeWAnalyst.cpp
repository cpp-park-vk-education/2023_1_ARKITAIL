#include "TreeNodeWAnalyst.hpp"

#include <memory>

#include "Calendar.hpp"
#include "Directory.hpp"
#include "Managers.hpp"
#include "Node.hpp"
#include "SessionScopeMap.hpp"
#include "Tag.hpp"
#include "TreeNodeWAnalystBase.hpp"
#include "User.hpp"

TreeNodeWAnalyst::TreeNodeWAnalyst() {}

TreeNodeWAnalyst::TreeNodeWAnalyst(IManagers* managers) :
    TreeNodeWAnalystBase(managers) {}

TreeNodeWConvertedData TreeNodeWAnalyst::analyseTreeNodeWChild(ITreeNode* tree_node) {
    Node node = tree_node->getNode();
    
    std::vector<Tag> tags;

    UserSptr user = managers_->user_manager()->get();
    TreeNodeWConvertedData data;

    if (tree_node->getParent() &&
        tree_node->getParent()->getNode().type & NodeType::SUBSCRIPTIONS_GROUP) {
        // тут только unsub, так как это подписки
        if (node.type & NodeType::PUBLIC_DIRECTORY) {
            DirectorySptr child = managers_->directory_manager()->get(node.resource_id);
            data = TreeNodeWConvertedData{TreeNodeWType::SUB_DIR_OPTIONS,
                                          child->name,
                                          child->description,
                                          tags,
                                          *managers_->user_manager()->get(child->owner_id),
                                          tree_node};

        } else {
            CalendarSptr child = managers_->calendar_manager()->get(node.resource_id);
            data = TreeNodeWConvertedData{TreeNodeWType::SUB_CALENDAR_OPTIONS,
                                          child->summary,
                                          child->description,
                                          tags,
                                          *managers_->user_manager()->get(child->owner_id),
                                          tree_node};
        }
    } else if (node.type & (NodeType::PRIVATE_CALENDAR | NodeType::PUBLIC_CALENDAR)) {
        CalendarSptr child = managers_->calendar_manager()->get(node.resource_id);

        data = TreeNodeWConvertedData{TreeNodeWType::PERSONAL_CALENDAR,
                                      child->summary,
                                      child->description,
                                      tags,
                                      *managers_->user_manager()->get(child->owner_id),
                                      tree_node};
    } else if (node.type & (NodeType::PRIVATE_DIRECTORY | NodeType::PUBLIC_DIRECTORY)) {
        DirectorySptr child = managers_->directory_manager()->get(node.resource_id);

        data = TreeNodeWConvertedData{TreeNodeWType::DIR,
                                      child->name,
                                      child->description,
                                      tags,
                                      *managers_->user_manager()->get(child->owner_id),
                                      tree_node};
    } else if (node.type & (NodeType::ROOT | 
                            NodeType::SUBSCRIPTIONS_GROUP | NodeType::PROFILE_GROUP)) {
        DirectorySptr child = managers_->directory_manager()->get(node.resource_id);
    std::cout << "ROOT" << std::endl;

        data = TreeNodeWConvertedData{TreeNodeWType::GROUP,
                                      child->name,
                                      child->description,
                                      tags,
                                      *managers_->user_manager()->get(child->owner_id),
                                      tree_node};
    } else if (node.type & (NodeType::PRIVATE_GROUP | NodeType::PUBLIC_GROUP)) {
    std::cout << "PRIVATE_GROUP" << std::endl;
        DirectorySptr child = managers_->directory_manager()->get(node.resource_id);

        data = TreeNodeWConvertedData{TreeNodeWType::GROUP_OPTIONS,
                                      child->name,
                                      child->description,
                                      tags,
                                      *managers_->user_manager()->get(child->owner_id),
                                      tree_node};
    } else if (node.type & NodeType::PROFILE) {
        ProfileSptr child = managers_->profile_manager()->get(node.resource_id);
        return TreeNodeWConvertedData{TreeNodeWType::PROFILE_LEAF, child->name, "",
                                      tags, *managers_->user_manager()->get(child->owner_id), tree_node->addChild(node)};
    }
    return data;
}
