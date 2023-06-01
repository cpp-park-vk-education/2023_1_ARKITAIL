#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WIconPair.h>
#include <Wt/WText.h>

#include <memory>
#include <vector>

#include "TreeNodeW.hpp"

class TreeNodeDirW : public TreeNodeW {
  public:
    TreeNodeDirW();
    TreeNodeDirW(ITreeNode* node);
    ~TreeNodeDirW() = default;
    TreeNodeW* addChildNode(std::unique_ptr<TreeNodeW> child) override;
    std::vector<TreeNodeW*> getChildrenNodes() override;
    void removeChildNode(TreeNodeW* child) override;
    void open() override;
    void showNode() override;
    void closeNode() override;
    void checkNode() override;
    void uncheckNode() override;
    void performAction(Action action) override;

  protected:
    std::vector<TreeNodeW*> children_;
    Wt::WIconPair* icon_;
    Wt::WContainerWidget* children_container_;
};
