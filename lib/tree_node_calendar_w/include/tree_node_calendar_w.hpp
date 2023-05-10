#pragma once

#include <Wt/WText.h>

#include "options_w.hpp"
#include "tree_node_w.hpp"

class TreeNodeCalendarW : public TreeNodeW {
  public:
    TreeNodeCalendarW(int id, std::string label);
    ~TreeNodeCalendarW() = default;

  private:
    Wt::WText* label_;
    OptionW* options_;
};
