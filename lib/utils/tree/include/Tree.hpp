#pragma once

#include <cstddef>

#include "Event.hpp"
#include "TreeNodeMock.hpp"

class Tree {
  public:
    Tree();
    Tree(const Node& node);

    ITreeNode* getRoot();

    std::vector<Event> getCheckedEvents();

    void checkNode(ITreeNode* node);
    void uncheckNode(ITreeNode* node);

    size_t checked();

  private:
    std::unique_ptr<ITreeNode> root_;
    size_t checked_;
};
