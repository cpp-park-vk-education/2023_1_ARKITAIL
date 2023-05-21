#pragma once

#include <memory>

#include "ITreeNode.hpp"
#include "User.hpp"
#include "options_w.hpp"

class TreeNodeW;

class TreeNodeWBuilderBase {
  protected:
    std::unique_ptr<TreeNodeW> tree_node_w;
    ITreeNode* node_;

  public:
    TreeNodeWBuilderBase();

    virtual TreeNodeWBuilderBase* createTreeNodeW(ITreeNode* node) = 0;

    TreeNodeWBuilderBase* addHead(std::unique_ptr<Wt::WWidget> head);
    TreeNodeWBuilderBase* addCheckBox();
    TreeNodeWBuilderBase* addOptions(std::unique_ptr<OptionsW> options);

    TreeNodeWBuilderBase* addToolTip(std::string description, std::vector<std::string> tags);
    TreeNodeWBuilderBase* addToolTip(std::string description, std::vector<std::string> tags,
                                     User author);
    TreeNodeWBuilderBase* addParent(TreeNodeW* parent_node);
    TreeNodeWBuilderBase* endNode();

    virtual std::unique_ptr<TreeNodeW> getTreeNodeW() = 0;

  private:
    std::unique_ptr<Wt::WContainerWidget> fillToolTipContainer(
        std::unique_ptr<Wt::WContainerWidget> content, std::string description,
        std::vector<std::string> tags);
    void addToolTip(std::unique_ptr<Wt::WContainerWidget> content);
};
