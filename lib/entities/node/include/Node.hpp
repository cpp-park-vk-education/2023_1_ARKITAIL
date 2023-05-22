#pragma once

#include <cstddef>

enum NodeType {
    ROOT = 1 << 1,
    PRIVATE_GROUP = 1 << 2,
    PRIVATE_DIRECTORY = 1 << 3,
    PRIVATE_CALENDAR = 1 << 4,
    PUBLIC_GROUP = 1 << 5,
    PUBLIC_DIRECTORY = 1 << 6,
    PUBLIC_CALENDAR = 1 << 7,
    SUBSCRIPTIONS_GROUP = 1 << 8,
    MOUNT = 1 << 9,
    PROFILE_GROUP = 1 << 10,
    PROFILE = 1 << 11
};

class Node {
  public:
    Node() = default;

    Node(int id, int parent_id, int rosource_id, NodeType type);

    Node(const Node& node);

    int id;
    int parent_id;
    int resource_id;

    NodeType type;
};
