#pragma once

#include "options_w.hpp"
#include "tree_node_dir_w.hpp"

class TreeNodeCalendarsDirW : public TreeNodeDirW {
  public:
    TreeNodeCalendarsDirW(int id, std::string label);
    ~TreeNodeCalendarsDirW() = default;
};
