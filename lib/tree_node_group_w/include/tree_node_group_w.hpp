#pragma once

#include <Wt/WInPlaceEdit.h>

#include "options_w.hpp"
#include "tree_node_w.hpp"

class TreeNodeGroupW : public TreeNodeW {
  public:
    TreeNodeGroupW();
    ~TreeNodeGroupW() = default;

  private:
    Wt::WInPlaceEdit* label_;
    OptionsW* options_;
};
