#include "Tree.hpp"
#include "Profile.hpp"
#include "TreeNode.hpp"

#include <Wt/WDate.h>
#include <Wt/WDateTime.h>

#include <queue>
#include <vector>

#include "Event.hpp"
#include "Managers.hpp"
#include "Node.hpp"
#include "SessionScopeMap.hpp"
#include "TreeNode.hpp"

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
            q.front()->isChecked()) {
            std::cout << "Calendar id: " << q.front()->getNode().resource_id << std::endl;
            for (auto e : mgr->calendar_manager()->getEvents(q.front()->getNode().resource_id)) {
                std::cout << "Event id: " << e.id << std::endl;
                v.push_back(e);
            }
        }

        for (auto c : q.front()->getChildren()) {
            std::cout << "Children node id: " << c->getNode().id << std::endl;
            q.push(c);
        }

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

    if (node->getNode().type & PROFILE) {
        Profile profile = mgr->profile_manager()->get(node->getNode().resource_id);

        q.push(root_.get());

        while (!q.empty()) {
            for (auto p : profile.nodes)
                if (p == q.front()->getNode().id) {
                    q.front()->check();
                    break;
                }

            for (auto c : q.front()->getChildren())
                q.push(c);

            q.pop();
        }

    } else {
        q.push(node);

        while (!q.empty()) {
            if (!q.front()->isChecked()) {
                q.front()->check();
        
                for (auto c : q.front()->getChildren())
                    q.push(c);
            }
        
            q.pop();
        }
    }
}

void Tree::uncheckNode(ITreeNode* node) {
    ITreeNode* cur_node = node;

    while (cur_node && cur_node->isChecked()) {
        cur_node->uncheck();
        cur_node = cur_node->getParent();
    }

    std::queue<ITreeNode*> q;
    q.push(node);

    while (!q.empty()) {
        q.front()->uncheck();

        for (auto c : q.front()->getChildren())
            q.push(c);

        q.pop();
    }
}

int Tree::checked() {
    return checked_;
}
