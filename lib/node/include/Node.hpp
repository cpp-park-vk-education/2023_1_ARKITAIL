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
        size_t rosource_id,
        NodeType type
    );

    Node(const Node& node);

    size_t id;
    size_t parent_id;
    size_t resource_id;

    NodeType type;

};


