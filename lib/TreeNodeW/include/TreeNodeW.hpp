#pragma once

#include <Wt/WCheckBox.h>
#include <Wt/WContainerWidget.h>

class TreeNodeW : public Wt::WContainerWidget {
  public:
    TreeNodeW(int id);
    ~TreeNodeW() = default;

    void removeNode();
    void checkNode();
    void unCheckNode();

  protected:
    Wt::WCheckBox* check_box_;
};
