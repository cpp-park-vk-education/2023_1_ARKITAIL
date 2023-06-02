#pragma once

#include <memory>

#include "ConnectionPoint.hpp"
#include "ITreeNode.hpp"
#include "OptionsW.hpp"
#include "TreeNodeWAnalystBase.hpp"
#include "User.hpp"
#include "Tag.hpp"

class TreeNodeW;
class TreeW;

class TreeNodeWBuilderBase {
  protected:
    std::unique_ptr<TreeNodeW> tree_node_w;
    ITreeNode* node_;

  public:
    virtual TreeNodeWBuilderBase* createTreeNodeW(ITreeNode* node) = 0;

    TreeNodeWBuilderBase* addAnalyst(std::unique_ptr<TreeNodeWAnalystBase> analyst);
    TreeNodeWBuilderBase* addHead(std::unique_ptr<Wt::WWidget> head);
    TreeNodeWBuilderBase* addTextHead(std::unique_ptr<Wt::WText> head);

    TreeNodeWBuilderBase* addCheckBoxConnectionPoint(
        ConnectionPoint<Wt::Signal<TreeNodeW*>, TreeW, TreeNodeW*>* cp);
    TreeNodeWBuilderBase* addCheckBox();

    TreeNodeWBuilderBase* addOptions(std::unique_ptr<OptionsW> options);

    TreeNodeWBuilderBase* addToolTip(std::string description, std::vector<Tag> tags);
    TreeNodeWBuilderBase* addToolTip(std::string description, std::vector<Tag> tags,
                                     User author);
    TreeNodeWBuilderBase* addParent(TreeNodeW* parent_node);
    TreeNodeWBuilderBase* endNode();

    virtual std::unique_ptr<TreeNodeW> getTreeNodeW() = 0;

  private:
    std::unique_ptr<Wt::WContainerWidget> fillToolTipContainer(
        std::unique_ptr<Wt::WContainerWidget> content, std::string description,
        std::vector<Tag> tags);
    void addToolTip(std::unique_ptr<Wt::WContainerWidget> content);
};
