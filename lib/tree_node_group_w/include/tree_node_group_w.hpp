#pragma once

#include <Wt/WInPlaceEdit.h>

#include "tree_node_leave_w.hpp"

class TreeNodeGroupW : public TreeNodeLeaveW {
  public:
    TreeNodeGroupW(std::string label);
    ~TreeNodeGroupW() = default;
    Wt::WInteractWidget* getTitle() override;

  private:
    Wt::WInPlaceEdit* label_;
    Wt::WString title_;

    void setTitle();
};
