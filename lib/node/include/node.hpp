#pragma once

#include <cstddef>

enum NodeType {
    PRIVATE,
    PUBLIC,
    SUBSCTIPTION,
    DIRECTORY,
    CALENDAR,
    MOUNT
};

class Node {
public:
    Node(
        size_t id,
        size_t parent_id,
        
    );

    Node(const Node& node);

    size_t id;
    size_t parent_id;
    NodeType type;
    size_t resource_id;

};


