#include "TreeNodeWSubAnalyst.hpp"

#include <memory>

#include "Calendar.hpp"
#include "Directory.hpp"
#include "Managers.hpp"
#include "Node.hpp"
#include "SessionScopeMap.hpp"
#include "Tag.hpp"
#include "User.hpp"
#include "Tag.hpp"

TreeNodeWSubAnalyst::TreeNodeWSubAnalyst(IManagers* managers) :
    TreeNodeWAnalystBase(managers) {}

TreeNodeWConvertedData TreeNodeWSubAnalyst::analyseTreeNodeWChild(ITreeNode* tree_node) {
    Node node = tree_node->getNode();
    UserSptr user = managers_->user_manager()->get();
    TreeNodeWConvertedData data;

    std::vector<Tag> tags;
    tags.push_back(*managers_->tag_manager()->get(1));
    tags.push_back(*managers_->tag_manager()->get(2));
    tags.push_back(*managers_->tag_manager()->get(3));

    if (node.type & NodeType::PUBLIC_CALENDAR) {
        CalendarSptr child = managers_->calendar_manager()->get(tree_node->getNode().resource_id);
        data = TreeNodeWConvertedData{TreeNodeWType::SUB_CALENDAR,
                                      child->summary,
                                      child->description,
                                      tags,
                                      *managers_->user_manager()->get(child->owner_id),
                                      tree_node};

    } else if (node.type & NodeType::PUBLIC_DIRECTORY) {
        DirectorySptr child = managers_->directory_manager()->get(tree_node->getNode().resource_id);
        data = TreeNodeWConvertedData{TreeNodeWType::SUB_DIR,
                                      child->name,
                                      child->description,
                                      tags,
                                      *managers_->user_manager()->get(child->owner_id),
                                      tree_node};
    }
    return data;
}
