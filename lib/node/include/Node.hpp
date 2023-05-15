#pragma once

#include <cstddef>

enum NodeType {
    ROOT                = 1 << 1,
    PRIVATE_GROUP       = 1 << 2,
    PRIVATE_DIRECTORY   = 1 << 3,
    PRIVATE_CALENDAR    = 1 << 4,
    PUBLIC_GROUP        = 1 << 5,
    PUBLIC_DIRECTORY    = 1 << 6,
    PUBLIC_CALENDAR     = 1 << 7,
    SUBSCRIPTIONS_GROUP = 1 << 8,
    MOUNT               = 1 << 9,
    PROFILE_GROUP       = 1 << 10,
    PROFILE             = 1 << 11
};

class Node {
public:
    Node() = default;

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

