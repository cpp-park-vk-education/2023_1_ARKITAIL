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
<<<<<<< HEAD
    auto mgr = SessionScopeMap::instance().get()->managers();
=======
    User user = managers_->user_manager()->get();
>>>>>>> origin/impl-bannikov
    TreeNodeWConvertedData data;

    std::vector<Tag> tags;

    if (node.type & NodeType::PUBLIC_CALENDAR) {
        CalendarSptr child = managers_->calendar_manager()->get(tree_node->getNode().resource_id);
        data = TreeNodeWConvertedData{TreeNodeWType::SUB_CALENDAR,
                                      child->summary,
                                      child->description,
                                      tags,
<<<<<<< HEAD
                                      *mgr->user_manager()->get(child->owner_id),
                                      tree_node};

    } else if (node.type & NodeType::PUBLIC_DIRECTORY) {
        DirectorySptr child = mgr->directory_manager()->get(tree_node->getNode().resource_id);
=======
                                      managers_->user_manager()->get(child->owner_id),
                                      tree_node};

    } else if (node.type & NodeType::PUBLIC_DIRECTORY) {
        Directory child = managers_->directory_manager()->get(tree_node->getNode().resource_id);
>>>>>>> origin/impl-bannikov
        data = TreeNodeWConvertedData{TreeNodeWType::SUB_DIR,
                                      child->name,
                                      child->description,
                                      tags,
<<<<<<< HEAD
                                      *mgr->user_manager()->get(child->owner_id),
=======
                                      managers_->user_manager()->get(child.owner_id),
>>>>>>> origin/impl-bannikov
                                      tree_node};
    }
    return data;
}
