#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WIconPair.h>
#include <Wt/WText.h>

#include <memory>
#include <string>
#include <vector>

#include "tree_node_w.hpp"

class TreeNodeDirW : public TreeNodeW {
  public:
    TreeNodeDirW(std::string label, ITreeNode* node);
    ~TreeNodeDirW() = default;
    TreeNodeW* addChildNode(std::unique_ptr<TreeNodeW> child) override;
    std::vector<TreeNodeW*> childrenNodes();
    void showNode() override;
    void closeNode() override;
    void checkNode() override;
    void uncheckNode() override;
    Wt::WInteractWidget* getTitle() override;
    void performAction(Action action) override;

  protected:
    std::vector<TreeNodeW*> children_;
    Wt::WIconPair* icon_;
    Wt::WText* label_;
    Wt::WContainerWidget* children_container_;
};
