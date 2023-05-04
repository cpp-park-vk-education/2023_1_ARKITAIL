#pragma once

#include "Node_db_model.hpp"

class node_manager {
public:
    nodes addNode(nodes);
    nodes deleteNode(int id);
    nodes upgradeNode(nodes);
};