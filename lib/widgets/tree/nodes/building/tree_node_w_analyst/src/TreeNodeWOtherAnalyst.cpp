#include "TreeNodeWOtherAnalyst.hpp"

#include <memory>

#include "Calendar.hpp"
#include "Directory.hpp"
#include "Managers.hpp"
#include "Node.hpp"
#include "SessionScopeMap.hpp"
#include "Tag.hpp"
#include "TreeNodeWAnalystBase.hpp"
#include "User.hpp"
#include "Tag.hpp"

TreeNodeWOtherAnalyst::TreeNodeWOtherAnalyst() {}

TreeNodeWOtherAnalyst::TreeNodeWOtherAnalyst(IManagers* managers) :
    TreeNodeWAnalystBase(managers) {}

TreeNodeWConvertedData TreeNodeWOtherAnalyst::analyseTreeNodeWChild(ITreeNode* tree_node) {
    Node node = tree_node->getNode();
    User user = managers_->user_manager()->get();
    TreeNodeWConvertedData data;

    std::vector<Tag> tags;

    auto is_sub = managers_->node_manager()->subscribed(node.id);
    if (node.type & NodeType::PUBLIC_GROUP) {
        Directory child = managers_->directory_manager()->get(node.resource_id);
        data = TreeNodeWConvertedData{
            (is_sub ? TreeNodeWType::OTHER_GROUP_SUB : TreeNodeWType::OTHER_GROUP_UNSUB),
            child.name,
            child.description,
            tags,
            managers_->user_manager()->get(child.owner_id),
            tree_node};

    } else if (node.type & NodeType::PUBLIC_DIRECTORY) {
        Directory child = managers_->directory_manager()->get(node.resource_id);
        data = TreeNodeWConvertedData{
            is_sub ? TreeNodeWType::OTHER_DIR_SUB : TreeNodeWType::OTHER_DIR_UNSUB,
            child.name,
            child.description,
            tags,
            managers_->user_manager()->get(child.owner_id),
            tree_node};

    } else {
        CalendarSptr child = managers_->calendar_manager()->get(node.resource_id);
        data = TreeNodeWConvertedData{
            is_sub ? TreeNodeWType::OTHER_CALENDAR_SUB : TreeNodeWType::OTHER_CALENDAR_UNSUB,
            child->summary,
            child->description,
            tags,
            managers_->user_manager()->get(child->owner_id),
            tree_node};
    }

    return data;
}
