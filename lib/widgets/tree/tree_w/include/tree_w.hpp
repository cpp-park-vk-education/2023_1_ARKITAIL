#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>

#include <vector>

#include "Node.hpp"
#include "Tree.hpp"
#include "TreeNode.hpp"
#include "tree_node_w.hpp"

class TreeW : public Wt::WContainerWidget {
  public:
    TreeW();
    ~TreeW() = default;
    void setRoot(const Node& node);
    void setRoot();

  private:
    std::unique_ptr<Tree> tree_manager_;
    Wt::WLineEdit* search_line_;
    Wt::WPushButton* remember_combination_button_;
    TreeNodeW* root_;

    void search();
    void rememberCombination();
};
