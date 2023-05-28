#pragma once

#include <Wt/WDate.h>
#include <Wt/WDateTime.h>
#include <cstddef>

#include "Event.hpp"
#include "TreeNodeMock.hpp"

class Tree {
  public:
    Tree(NodeSptr node);

    ITreeNode* getRoot();

    std::vector<Event> getCheckedEvents();
    std::vector<Event> getCheckedEventsByInterval(Wt::WDateTime begin, Wt::WDateTime end);

    void checkNode(ITreeNode* node);
    void uncheckNode(ITreeNode* node);

    int checked();

  private:
    std::unique_ptr<ITreeNode> root_;
    int checked_;
};
