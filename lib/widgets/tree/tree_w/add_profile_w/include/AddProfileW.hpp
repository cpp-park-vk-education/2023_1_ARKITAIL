#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>

#include <vector>

#include "TreeNodeW.hpp"

class AddProfileW : public Wt::WContainerWidget {
  public:
    AddProfileW(TreeNodeW* profile_group);
    ~AddProfileW() = default;

    Wt::Signal<Node*>& profileAdded();
    Wt::Signal<>& needCheckedNodes();

    void setButtonEnabled(bool value);
    void addProfileW(std::vector<size_t> nodes);

  private:
    TreeNodeW* profile_group_;
    Wt::WLineEdit* input_name_;
    Wt::WPushButton* remember_combination_button_;

    Wt::Signal<Node*> profile_added_;
    Wt::Signal<> need_checked_nodes_;

    void validate();
};
