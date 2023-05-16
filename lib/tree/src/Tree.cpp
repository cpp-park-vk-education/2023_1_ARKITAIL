#include <queue>
#include <vector>

#include "Event.hpp"
#include "Managers.hpp"
#include "Tree.hpp"
#include "Node.hpp"
#include "TreeNode.hpp"

Tree::Tree(const Node& node) :
    root_(std::make_unique<TreeNode>(TreeNode(node, nullptr))),
    checked_(0) {}

TreeNode* Tree::getRoot() {
    return root_.get();
}

std::vector<Event> Tree::getCheckedEvents() {
    std::queue<TreeNode*> q;
    std::vector<Event> v;

    q.push(getRoot());

    while (!q.empty()) {
        if ((q.front()->getNode().type & (NodeType::PUBLIC_CALENDAR | NodeType::PRIVATE_CALENDAR)) && q.front()->isChecked())
            for (auto e : Managers::instance().calendar_manager->getEvents(q.front()->getNode().resource_id))
                v.push_back(e);

        for (auto c : q.front()->getChildren())
            q.push(c);

        q.pop();
    }

    return v;
}

std::vector<Event> Tree::checkNode(TreeNode* node) {
    std::queue<TreeNode*> q;
    std::vector<Event> v;

    q.push(node);

    while (!q.empty()) {
        if (q.front()->isChecked()) {
            q.front()->check();
            
            if (q.front()->getNode().type & (NodeType::PUBLIC_DIRECTORY | NodeType::PUBLIC_DIRECTORY))
                for (auto e : Managers::instance().calendar_manager->getEvents(q.front()->getNode().resource_id))
                    v.push_back(e);
            
            for (auto c : q.front()->getChildren())
                q.push(c);
        }
            
        q.pop();
    }

    return v;
}

void Tree::uncheckNode(TreeNode* node) {
    TreeNode* cur_node = node;

    while (cur_node->isChecked()) {
        cur_node->uncheck();
        cur_node = cur_node->getParent();
    }
}

size_t Tree::checked() {
    return checked_;
}

