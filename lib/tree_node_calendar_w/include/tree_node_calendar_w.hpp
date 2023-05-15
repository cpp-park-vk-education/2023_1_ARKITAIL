#pragma once

#include <Wt/WText.h>

#include "tree_node_leave_w.hpp"

class TreeNodeCalendarW : public TreeNodeLeaveW {
  public:
    TreeNodeCalendarW(std::string label);
    ~TreeNodeCalendarW() = default;
    Wt::WInteractWidget* getTitle() override;

  private:
    Wt::WText* label_;
};
