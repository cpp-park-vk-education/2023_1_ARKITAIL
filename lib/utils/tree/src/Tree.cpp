#include "Tree.hpp"
#include "TreeNode.hpp"

#include <Wt/WDate.h>
#include <Wt/WDateTime.h>
#include <queue>
#include <vector>

#include "Event.hpp"
#include "Managers.hpp"
#include "Node.hpp"
#include "SessionScopeMap.hpp"

Tree::Tree(const Node& node) :
    root_(std::make_unique<TreeNode>(node, nullptr)),
    checked_(0) {}

ITreeNode* Tree::getRoot() {
    return root_.get();
}

std::vector<Event> Tree::getCheckedEvents() {
    auto mgr = SessionScopeMap::instance().get()->managers();
    
    std::queue<ITreeNode*> q;
    std::vector<Event> v;

    q.push(getRoot());

    while (!q.empty()) {
        if ((q.front()->getNode().type & (PUBLIC_CALENDAR | PRIVATE_CALENDAR)) &&
            q.front()->isChecked())
            for (auto e : mgr->calendar_manager()->getEvents(q.front()->getNode().resource_id))
                v.push_back(*e);

        for (auto c : q.front()->getChildren()) q.push(c);

        q.pop();
    }

    return v;
}

std::vector<Event> Tree::getCheckedEventsByInterval(Wt::WDateTime begin, Wt::WDateTime end) {
    std::vector<Event> v;

    for (auto e : getCheckedEvents())
        if (e.start <= end && e.end >= begin)
            v.push_back(e);

    return v;
}

void Tree::checkNode(ITreeNode* node) {
    auto mgr = SessionScopeMap::instance().get()->managers();

    std::queue<ITreeNode*> q;

    q.push(node);

    while (!q.empty()) {
        if (q.front()->isChecked()) {
            q.front()->check();

            for (auto c : q.front()->getChildren())
                q.push(c);
        }

        q.pop();
    }
}

void Tree::uncheckNode(ITreeNode* node) {
    ITreeNode* cur_node = node;

    while (cur_node->isChecked()) {
        cur_node->uncheck();
        cur_node = cur_node->getParent();
    }

    std::queue<ITreeNode*> q;
    q.push(node);

    while (q.empty()) {
        q.front()->uncheck();
        
        for (auto c : q.front()->getChildren())
            q.push(c);

        q.pop();
    }
}

size_t Tree::checked() {
    return checked_;
}
