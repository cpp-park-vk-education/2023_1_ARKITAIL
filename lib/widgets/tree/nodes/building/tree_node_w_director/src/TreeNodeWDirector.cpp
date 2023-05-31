#include "TreeNodeWDirector.hpp"

#include <Wt/WAnchor.h>
#include <Wt/WBreak.h>

#include "ITreeNode.hpp"
#include "InPlaceEditTitle.hpp"
#include "Managers.hpp"
#include "Node.hpp"
#include "OptionsW.hpp"
#include "OptionsWBuilder.hpp"
#include "OptionsWDirector.hpp"
#include "SessionScopeMap.hpp"
#include "TreeNodeDirWBuilder.hpp"
#include "TreeNodeLeafW.hpp"
#include "TreeNodeLeafWBuilder.hpp"
#include "TreeNodeWAnalyst.hpp"
#include "TreeNodeWAnalystBase.hpp"
#include "TreeNodeWBuilderBase.hpp"
#include "TreeNodeWOtherAnalyst.hpp"
#include "TreeNodeWSubAnalyst.hpp"

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
        node_builder->addAnalyst(
            std::make_unique<TreeNodeWOtherAnalyst>(SessionScopeMap::instance().get()->managers()));
    } else if (data.components_set & Components::TYPE_SUB_DIR) {
        node_builder->addAnalyst(
            std::make_unique<TreeNodeWSubAnalyst>(SessionScopeMap::instance().get()->managers()));
    }

    if (data.components_set & Components::CHECKBOX) {
        node_builder->addCheckBox();
        auto cm = SessionScopeMap::instance().get()->connections_mediator();
        if (data.components_set == TreeNodeWType::OTHER_CALENDAR_SUB ||
            data.components_set == TreeNodeWType::OTHER_CALENDAR_UNSUB) {
            node_builder->addCheckBoxConnectionPoint(&cm->node_to_tree_other);
        } else {
            node_builder->addCheckBoxConnectionPoint(&(cm->node_to_tree_main));
        }
    }

    if (data.components_set & Components::LABEL) {
        std::cout << data.name << std::endl;
        node_builder->addHead(std::make_unique<InPlaceEditTitle>(data.name));
    } else {
        node_builder->addTextHead(std::make_unique<Wt::WText>(data.name));
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
