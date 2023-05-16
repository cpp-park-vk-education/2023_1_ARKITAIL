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
    void setRoot(Node* node);
    void setRoot();

  private:
    Tree* tree_manager_;
    Wt::WLineEdit* search_line_;
    Wt::WPushButton* remember_combination_button_;
    TreeNodeW* root_;
    std::vector<std::unique_ptr<OptionsW>> options_;

    void search();
    void rememberCombination();
};
