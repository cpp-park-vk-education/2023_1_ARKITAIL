#include "NodeDbManagerMock.hpp"

#include <memory>
#include <string>
#include <utility>

#include "DbManagers.hpp"
#include "DbMock.hpp"
#include "Node.hpp"
#include "NodeDbManagerMock.hpp"
#include "Tag.hpp"
#include "TagDbManagerMock.hpp"

NodeDbManagerMock::NodeDbManagerMock(std::shared_ptr<DbMock> db) :
    db_(db),
    aid_(db_->nodes.size()) {}

NodeSptr NodeDbManagerMock::get(int node_id) {
    for (auto e = db_->nodes.begin() + 1; e != db_->nodes.end(); e++) {
        if (e->id == node_id) {
            return std::make_shared<Node>(*e);
        }
    }

    return std::make_shared<Node>(db_->nodes[0]);
}

int NodeDbManagerMock::add(NodeSptr node) {
    db_->nodes.emplace_back(
        aid_, node->parent_id, node->resource_id, node->owner_id, node->type);

    return aid_++;
}

void NodeDbManagerMock::update(NodeSptr node) {
    for (auto e = db_->nodes.begin() + 1; e != db_->nodes.end(); e++)
        if (e->id == node->id) {
            *e = *node;
            break;
        }
}

void NodeDbManagerMock::remove(int node_id) {
    for (auto e = db_->nodes.begin() + 1; e != db_->nodes.end(); e++)
        if (e->id == node_id) {
            db_->nodes.erase(e);
            break;
        }
}

std::vector<Node> NodeDbManagerMock::getChildren(int node_id) {
    std::vector<Node> children;

    for (auto e : db_->nodes)
        if (e.parent_id == node_id && e.id != node_id)
            children.push_back(e);

    return children;
}

void NodeDbManagerMock::tag(int node_id, int tag_id) {
    db_->tags_to_nodes.push_back(std::make_pair(node_id, tag_id));
}

std::vector<TagSptr> NodeDbManagerMock::tagByNode(int node_id) {
    std::vector<TagSptr> ts;

    for (auto tn : db_->tags_to_nodes)
        if (tn.second == node_id)
            for (auto e = db_->tags.begin() + 1; e != db_->tags.end(); e++)
                if (e->id == tn.first) {
                    ts.push_back(std::make_shared<Tag>(*e));
                    break;
                };

    return ts;
}

