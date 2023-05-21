#include "tree_node_w_director.hpp"

#include <Wt/WAnchor.h>
#include <Wt/WBreak.h>

#include "ITreeNode.hpp"
#include "Node.hpp"
#include "in_place_edit_title.hpp"
#include "options_w_builder.hpp"
#include "options_w_director.hpp"
#include "tree_node_dir_w_builder.hpp"
#include "tree_node_leaf_w_builder.hpp"
#include "tree_node_other_dir_w_builder.hpp"
#include "tree_node_sub_dir_w_builder.hpp"
#include "tree_node_w.hpp"
#include "tree_node_w_builder_base.hpp"

TreeNodeWDirector::TreeNodeWDirector() {}

std::unique_ptr<TreeNodeW> TreeNodeWDirector::createNode(TreeNodeWConvertedData data) {
    if (data.components_set & Components::TYPE_DIR) {
        std::cout << "собралось" << std::endl;
        node_builder = std::make_unique<TreeNodeDirWBuilder>();
    }
    // else if (data.components_set & Components::TYPE_OTHER_DIR) {
    //     node_builder_ptr = TreeNodeOtherDirWBuilder().createTreeNodeW(data.tree_node);
    // } else if (data.components_set & Components::TYPE_SUB_DIR) {
    //     node_builder_ptr = TreeNodeSubDirWBuilder().createTreeNodeW(data.tree_node);
    // } else {
    //     node_builder_ptr = TreeNodeLeafWBuilder().createTreeNodeW(data.tree_node);
    // }

    auto node_builder_ptr = node_builder->createTreeNodeW(data.tree_node);

    if (data.components_set & Components::CHECKBOX) {
        node_builder_ptr->addCheckBox();
    }

    if (data.components_set & Components::LABEL) {
        node_builder_ptr->addHead(std::make_unique<InPlaceEditTitle>(data.name));
    } else {
        node_builder_ptr->addHead(std::make_unique<Wt::WText>(data.name));
    }

    OptionsWBuilder options_builder;

    if (data.components_set & Components::OPTIONS_CALENDARS_DIR) {
        node_builder_ptr->addOptions(
            OptionsWDirector().createOptionsCalendarsDirW(options_builder));
    } else if (data.components_set & Components::OPTIONS_PERSONAL_CALENDAR) {
        node_builder_ptr->addOptions(
            OptionsWDirector().createOptionsPersonalCalendarW(options_builder));
    } else if (data.components_set & Components::OPTIONS_PROFILE) {
        node_builder_ptr->addOptions(OptionsWDirector().createOptionsProfileW(options_builder));
    } else if (data.components_set & Components::OPTIONS_SUB) {
        node_builder_ptr->addOptions(
            OptionsWDirector().createOptionsSubscriptionW(options_builder));
    } else if (data.components_set & Components::OPTIONS_UNSUB) {
        node_builder_ptr->addOptions(
            OptionsWDirector().createOptionsUnsubscriptionW(options_builder));
    }
    if (data.description != "" || data.tags.size() != 0) {
        if (data.components_set & Components::TOOLTIP_AUTHOR) {
            node_builder_ptr->addToolTip(data.description, data.tags, data.author);
        } else {
            node_builder_ptr->addToolTip(data.description, data.tags);
        }
    }
    node_builder_ptr->endNode();

    return node_builder_ptr->getTreeNodeW();
}
