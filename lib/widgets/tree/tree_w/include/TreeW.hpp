#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>

#include <vector>

#include "Event.hpp"
#include "Node.hpp"
#include "Tree.hpp"
#include "TreeNode.hpp"
#include "TreeNodeW.hpp"

class TreeW : public Wt::WContainerWidget {
  public:
    TreeW();
    ~TreeW() = default;
    void setRoot(const Node& node);
    void checkNode(ITreeNode* tree_node);
    void getRangeEvents(Wt::WDate date1, Wt::WDate date2);

    Wt::Signal<> node_checked;
    Wt::Signal<Wt::WDate, std::vector<Event>> events_getted;

  private:
    std::unique_ptr<Tree> tree_manager_;
    Wt::WLineEdit* search_line_;
    Wt::WPushButton* remember_combination_button_;
    TreeNodeW* root_;

    void search();
    void rememberCombination();
};
