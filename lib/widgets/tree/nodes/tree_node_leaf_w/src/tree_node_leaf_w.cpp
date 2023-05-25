#include "tree_node_leaf_w.hpp"

#include <memory>

#include "Calendar.hpp"
#include "EditCalendarDialog.hpp"
#include "Managers.hpp"
#include "Node.hpp"
#include "SessionScopeMap.hpp"
#include "TreeNode.hpp"
#include "tree_node_w.hpp"

TreeNodeLeafW::TreeNodeLeafW() {}

TreeNodeLeafW::TreeNodeLeafW(ITreeNode* node) :
    TreeNodeW(node) {}

void TreeNodeLeafW::checkNode() {
    node_->check();
    check_box_->setChecked(true);
}

void TreeNodeLeafW::uncheckNode() {
    uncheckParentNodes();
}

void TreeNodeLeafW::performAction(Action action) {
    TreeNodeW::performAction(action);
    switch (action) {
        case Action::EDIT: {
            auto mgr = SessionScopeMap::instance().get()->managers();
            CalendarSptr dummy_calendar =
                mgr->calendar_manager()->get(node_->getNode().resource_id);

            dialog::EditCalendarDialog* dialog =
                addChild(std::make_unique<dialog::EditCalendarDialog>(dummy_calendar));

            dialog->show();

            // dialog.calendar_updated().connect(...);

            dialog->finished().connect([=] {
                removeChild(dialog);
                Wt::log("EditCalendarDialog removed");
            });
            break;
        }
    }
}
