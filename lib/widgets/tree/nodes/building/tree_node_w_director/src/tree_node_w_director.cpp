#include "tree_node_w_director.hpp"

#include <Wt/WAnchor.h>
#include <Wt/WBreak.h>

#include "ITreeNode.hpp"
#include "ITreeNodeWAnalyst.hpp"
#include "Node.hpp"
#include "TreeNodeDirWBuilder.hpp"
#include "TreeNodeLeafWBuilder.hpp"
#include "TreeNodeWAnalyst.hpp"
#include "TreeNodeWBuilderBase.hpp"
#include "TreeNodeWOtherAnalyst.hpp"
#include "TreeNodeWSubAnalyst.hpp"
#include "in_place_edit_title.hpp"
#include "options_w.hpp"
#include "options_w_builder.hpp"
#include "options_w_director.hpp"
#include "tree_node_leaf_w.hpp"
#include "tree_node_w_director.hpp"

TreeNodeWDirector::TreeNodeWDirector() {}

std::unique_ptr<TreeNodeW> TreeNodeWDirector::fillNode(TreeNodeWConvertedData data) {
    std::unique_ptr<TreeNodeWBuilderBase> node_builder_ptr;
    if (data.components_set & Components::TYPE_LEAF) {
        node_builder_ptr = std::make_unique<TreeNodeLeafWBuilder>();

    } else {
        node_builder_ptr = std::make_unique<TreeNodeDirWBuilder>();
    }
    auto node_builder = node_builder_ptr->createTreeNodeW(data.tree_node);

    if (data.components_set & Components::TYPE_OTHER_DIR) {
        node_builder->addAnalyst(std::make_unique<TreeNodeWOtherAnalyst>());
    } else if (data.components_set & Components::TYPE_SUB_DIR) {
        node_builder->addAnalyst(std::make_unique<TreeNodeWSubAnalyst>());
    }

    if (data.components_set & Components::CHECKBOX) {
        node_builder->addCheckBox();
    }

    if (data.components_set & Components::LABEL) {
        node_builder->addHead(std::make_unique<InPlaceEditTitle>(data.name));
    } else {
        node_builder->addHead(std::make_unique<Wt::WText>(data.name));
    }

    OptionsWBuilder options_builder;

    if (data.components_set & Components::OPTIONS_CALENDARS_DIR) {
        node_builder->addOptions(OptionsWDirector().createOptionsCalendarsDirW(options_builder));
    } else if (data.components_set & Components::OPTIONS_PERSONAL_CALENDAR) {
        node_builder->addOptions(
            OptionsWDirector().createOptionsPersonalCalendarW(options_builder));
    } else if (data.components_set & Components::OPTIONS_PROFILE) {
        node_builder->addOptions(OptionsWDirector().createOptionsProfileW(options_builder));
    } else if (data.components_set & Components::OPTIONS_SUB) {
        node_builder->addOptions(OptionsWDirector().createOptionsSubscriptionW(options_builder));
    } else if (data.components_set & Components::OPTIONS_UNSUB) {
        node_builder->addOptions(OptionsWDirector().createOptionsUnsubscriptionW(options_builder));
    }
    if (data.description != "" || data.tags.size() != 0) {
        if (data.components_set & Components::TOOLTIP_AUTHOR) {
            node_builder->addToolTip(data.description, data.tags, data.author);
        } else {
            node_builder->addToolTip(data.description, data.tags);
        }
    }
    node_builder->endNode();

    return node_builder->getTreeNodeW();
}
