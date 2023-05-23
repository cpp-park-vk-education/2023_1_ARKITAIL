#include "TreeNodeWOtherAnalyst.hpp"

#include <memory>

#include "Calendar.hpp"
#include "Directory.hpp"
#include "Managers.hpp"
#include "Node.hpp"
#include "SessionScopeMap.hpp"
#include "Tag.hpp"
#include "User.hpp"

TreeNodeWOtherAnalyst::TreeNodeWOtherAnalyst() {}

TreeNodeWConvertedData TreeNodeWOtherAnalyst::analyseTreeNodeWChild(ITreeNode* tree_node) {
    Node node = tree_node->getNode();
    auto mgr = SessionScopeMap::instance().get()->managers();
    User user = mgr->user_manager()->get();
    TreeNodeWConvertedData data;

    std::vector<std::string> tags;

    // нужна проверка на sub/unsub
    if (node.type & NodeType::PUBLIC_GROUP) {
        Directory child = mgr->directory_manager()->get(node.resource_id);
        data = TreeNodeWConvertedData{
            TreeNodeWType::OTHER_GROUP_SUB,           child.name, child.description, tags,
            mgr->user_manager()->get(child.owner_id), tree_node};

    } else if (node.type & NodeType::PUBLIC_DIRECTORY) {
        Directory child = mgr->directory_manager()->get(node.resource_id);
        data = TreeNodeWConvertedData{TreeNodeWType::OTHER_DIR_SUB,
                                      child.name,
                                      child.description,
                                      tags,
                                      mgr->user_manager()->get(child.owner_id),
                                      tree_node};

    } else {
        Calendar child = mgr->calendar_manager()->get(node.resource_id);
        data = TreeNodeWConvertedData{
            TreeNodeWType::OTHER_CALENDAR_SUB,        child.name, child.description, tags,
            mgr->user_manager()->get(child.owner_id), tree_node};
    }

    return data;
}
