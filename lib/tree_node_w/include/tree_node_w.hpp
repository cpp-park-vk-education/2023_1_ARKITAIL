#pragma once
#include <Wt/WCheckBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WHBoxLayout.h>

#include "options_w.hpp"

class TreeNodeW : public Wt::WContainerWidget {
  public:
    TreeNodeW();
    virtual ~TreeNodeW() = default;
    TreeNodeW* addOptions(std::unique_ptr<OptionsW> options);
    void removeNode();
    TreeNodeW* endNode();
    virtual TreeNodeW* addChildNode(std::unique_ptr<TreeNodeW> child) {}
    virtual void checkNode() = 0;
    virtual void uncheckNode() = 0;
    void hideCheckBox();
    virtual void showNode() = 0;
    virtual void closeNode() = 0;

  protected:
    Wt::WHBoxLayout* node_block_;
    OptionsW* options_;
    Wt::WCheckBox* check_box_;
};
