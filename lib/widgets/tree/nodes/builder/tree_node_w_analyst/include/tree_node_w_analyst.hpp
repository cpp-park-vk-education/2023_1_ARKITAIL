#pragma once

#include <memory>

#include "Node.hpp"

enum TreeNoddeWType {
    PUBLIC_GROUP,
    PRIVATE_GROUP,
    OTHER_GROUP,
    GROUP,

    PRIVATE_DIRECTORY,
    PRIVATE_CALENDAR,

    PUBLIC_DIRECTORY,
    PUBLIC_CALENDAR,

    SUBSCRIPTIONS_GROUP,
    MOUNT,

    PROFILE_GROUP,
    PROFILE,
}

class TreeNodeWAnalyst {
  public:
    TreeNodeWAnalyst();
    ~TreeNodeWAnalyst() = default;

    TreeNodeWBuilder& analyseTreeNodeDirWChild(TypeNode type);
    TreeNodeWBuilder& analyseTreeNodeOtherDirWChild(TypeNode type);
    TreeNodeWBuilder& analyseTreeNodeSubscriptionDirWChild(TypeNode type);
};
