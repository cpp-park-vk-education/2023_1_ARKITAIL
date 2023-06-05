#include "TreeNodeLeafW.hpp"

#include <Wt/WGlobal.h>
#include <memory>

#include "Calendar.hpp"
#include "EditCalendarDialog.hpp"
#include "Managers.hpp"
#include "Node.hpp"
#include "SessionScopeMap.hpp"
#include "TreeNode.hpp"
#include "TreeNodeW.hpp"

TreeNodeLeafW::TreeNodeLeafW() :
    TreeNodeW() {}

TreeNodeLeafW::TreeNodeLeafW(ITreeNode* node) :
    TreeNodeW(node) {}

void TreeNodeLeafW::checkNode() {
    if (check_box_->checkState() == Wt::CheckState::Checked) {
        checked_.emit(this);
    }
    check_box_->setChecked(true);
}

void TreeNodeLeafW::uncheckNode() {
    if (check_box_->checkState() == Wt::CheckState::Unchecked)
        checked_.emit(this);
    uncheckParentNodes();
}

void TreeNodeLeafW::performAction(Action action) {
    TreeNodeW::performAction(action);
    switch (action) {
        case Action::EDIT: {
            auto mgr = SessionScopeMap::instance().get()->managers();
            CalendarSptr calendar =
                mgr->calendar_manager()->get(node_->getNode().resource_id);

            dialog::EditCalendarDialog* dialog =
                addChild(std::make_unique<dialog::EditCalendarDialog>(calendar));

            dialog->show();

            dialog->calendar_updated().connect([=](CalendarSptr calendar) {
                text_title_->setText(calendar->summary);
            });

            dialog->finished().connect([=] {
                removeChild(dialog);
                Wt::log("EditCalendarDialog removed");
            });
            break;
        }
    }
}
