#pragma once

#include "OptionsW.hpp"
#include "TreeNodeDirW.hpp"

class TreeNodeCalendarsDirW : public TreeNodeDirW {
  public:
    TreeNodeGroupCalendarsW(int id, std::string label);
    ~TreeNodeCalendarsDirW() = default;

  private:
    OptionsW* options_;
};
