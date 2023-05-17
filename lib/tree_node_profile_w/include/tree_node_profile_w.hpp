#pragma once

#include <Wt/WInPlaceEdit.h>

#include "tree_node_leaf_w.hpp"

class TreeNodeProfileW : public TreeNodeLeafW {
  public:
    TreeNodeProfileW(std::string label, ITreeNode* node);
    ~TreeNodeProfileW() = default;
    Wt::WInteractWidget* getTitle() override;

  private:
    Wt::WInPlaceEdit* label_;
    Wt::WString title_;

    void setTitle();
};
