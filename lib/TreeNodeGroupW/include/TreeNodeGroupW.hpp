#pragma once

#include <Wt/WInPlaceEdit.h>

#include "OptionsW.hpp"
#include "TreeNodeW.hpp"

class TreeNodeGroupW : public TreeNodeW {
  public:
    TreeNodeGroupW();
    ~TreeNodeGroupW() = default;

  private:
    Wt::WInPlaceEdit* label_;
    OptionsW* options_;
};
