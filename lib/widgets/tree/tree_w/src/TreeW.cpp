#include "TreeW.hpp"

#include <Wt/WAnimation.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDate.h>
#include <Wt/WDateTime.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WTime.h>

#include <algorithm>
#include <memory>
#include <string>
#include <queue>

#include "AddProfileW.hpp"
#include "ITreeNode.hpp"
#include "Managers.hpp"
#include "Node.hpp"
#include "OtherUserW.hpp"
#include "SessionScopeMap.hpp"
#include "Tree.hpp"
#include "TreeNode.hpp"
#include "TreeNodeDirW.hpp"
#include "TreeNodeLeafW.hpp"
#include "TreeNodeWAnalyst.hpp"
#include "TreeNodeWDirector.hpp"
#include "TreeNodeWOtherAnalyst.hpp"

TreeW::TreeW() :
    tree_manager_(),
    header_(),
    add_profile_w_(),
    root_() {

    animateHide(Wt::WAnimation(Wt::AnimationEffect::SlideInFromLeft));
    setStyleClass("start-0 w-100");
}

void TreeW::setRoot(const Node& node) {

    auto mgr = SessionScopeMap::instance().get()->managers();

    tree_manager_ = std::make_unique<Tree>(node);

    auto tree_node = tree_manager_->getRoot();

    header_ = addWidget(std::make_unique<Wt::WContainerWidget>());
    
    root_ = addWidget(TreeNodeWDirector().fillNode(TreeNodeWAnalyst(mgr).analyseTreeNodeWChild(tree_node)));

    root_->open();

    for (auto group : root_->getChildrenNodes()) {

        if(group->getType() & NodeType::PROFILE_GROUP){
            add_profile_w_ = header_->addWidget(std::make_unique<AddProfileW>(group));
        }
    }

    add_profile_w_->needCheckedNodes().connect(this, &TreeW::sendCheckedNodes);
}

void TreeW::setRoot(const Node& node, const User& user) {
    if (header_) {
        removeChild(header_);
    }

    header_ = addWidget(std::make_unique<OtherUserW>(user));

    if (root_) {
        removeChild(root_);
    }
    auto mgr = SessionScopeMap::instance().get()->managers();

    tree_manager_ = std::make_unique<Tree>(node);

    auto tree_node = tree_manager_->getRoot();

    root_ = addWidget(
        TreeNodeWDirector().fillNode(TreeNodeWOtherAnalyst(mgr).analyseTreeNodeWChild(tree_node)));
}

void TreeW::checkNode(TreeNodeW* tree_node_w) {
    auto tree_node = tree_node_w->getTreeNode();
    size_t check_nodes_count = getCheckedNodes().size();
    if (tree_node_w->isCheck()) {
        tree_manager_->checkNode(tree_node);
        if (check_nodes_count > 1) {
            add_profile_w_->setButtonEnabled(true);
        }
    } else {
        tree_manager_->uncheckNode(tree_node);
        if (check_nodes_count < 2) {
            add_profile_w_->setButtonEnabled(false);
        }
    }
    std::cout << "\nnode_checked из дерева => выпущен сигнал в хедер\n" << std::endl;
    node_checked.emit();
}

void TreeW::getRangeEvents(Wt::WDate date1, Wt::WDate date2) {
    auto events = tree_manager_->getCheckedEventsByInterval(
        Wt::WDateTime(date1, Wt::WTime(0, 0, 0)), Wt::WDateTime(date2, Wt::WTime(0, 0, 0)));
    std::cout << events.size() << "\n";
    for (auto e : events) {
        std::cout << e.summary << std::endl;
    }

    std::cout << "\nпо двум датам получили события и отправили в тело календаря\n" << std::endl;
    events_getted.emit(date1, events);
}

void TreeW::sendCheckedNodes() {
    add_profile_w_->addProfileW(getCheckedNodes());
}

std::vector<size_t> TreeW::getCheckedNodes() {
    std::queue<TreeNodeW*> q;
    std::vector<size_t> v;

    q.push(root_);

    while (!q.empty()) {
        if (!(q.front()->getType() & NodeType::PROFILE_GROUP)) {

            if(q.front()->isCheck()) {
                size_t node_id = q.front()->getTreeNode()->getNode().id;
                v.push_back(node_id);
            } else {
                for (auto child : q.front()->getChildrenNodes()) {
                    q.push(child);
                }
            }
        }

        q.pop();
    }

    return v;
}

