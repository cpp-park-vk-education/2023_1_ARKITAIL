#include "TreeNodeWSubAnalyst.hpp"

#include <memory>

#include "Calendar.hpp"
#include "Directory.hpp"
#include "Managers.hpp"
#include "Node.hpp"
#include "SessionScopeMap.hpp"
#include "Tag.hpp"
#include "User.hpp"

TreeNodeWSubAnalyst::TreeNodeWSubAnalyst() {}

TreeNodeWConvertedData TreeNodeWSubAnalyst::analyseTreeNodeWChild(ITreeNode* tree_node) {
    std::cout << "TreeNodeWSubAnalyst\n\n";

    Node node = tree_node->getNode();
    auto mgr = SessionScopeMap::instance().get()->managers();
    User user = mgr->user_manager()->get();
    TreeNodeWConvertedData data;

    std::vector<std::string> tags;

    if (node.type & NodeType::PUBLIC_CALENDAR) {
        CalendarSptr child = mgr->calendar_manager()->get(tree_node->getNode().resource_id);
        data = TreeNodeWConvertedData{TreeNodeWType::SUB_CALENDAR,
                                      child->summary,
                                      child->description,
                                      tags,
                                      mgr->user_manager()->get(child->owner_id),
                                      tree_node};

    } else if (node.type & NodeType::PUBLIC_DIRECTORY) {
        Directory child = mgr->directory_manager()->get(tree_node->getNode().resource_id);
        data = TreeNodeWConvertedData{TreeNodeWType::SUB_DIR,
                                      child.name,
                                      child.description,
                                      tags,
                                      mgr->user_manager()->get(child.owner_id),
                                      tree_node};
    }
    return data;
}
