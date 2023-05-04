#pragma once

#include <Wt/WText.h>

#include "OptionsW.hpp"
#include "TreeNodeW.hpp"

class TreeNodeCalendarW : public TreeNodeW {
  public:
    TreeNodeCalendarW(int id, std::string label);
    ~TreeNodeCalendarW() = default;

  private:
    Wt::WText* label_;
    OptionW* options_;
};
