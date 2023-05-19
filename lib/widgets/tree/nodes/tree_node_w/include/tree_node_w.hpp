#pragma once

#include <Wt/WCheckBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WPopupWidget.h>

#include <memory>

#include "Calendar.hpp"
#include "Directory.hpp"
#include "ITreeNode.hpp"
#include "Node.hpp"
#include "Tree.hpp"
#include "User.hpp"
#include "options_w.hpp"
#include "tree_node_w_builder.hpp"

class TreeNodeW : public Wt::WContainerWidget {
    friend class TreeNodeWBuilder;

  public:
    TreeNodeW(ITreeNode* node);
    virtual ~TreeNodeW() = default;
    virtual void checkNode() = 0;
    virtual void uncheckNode() = 0;
    virtual void showNode() = 0;
    virtual void closeNode() = 0;
    virtual void performAction(Action action) = 0;

    virtual TreeNodeW* addChildNode(std::unique_ptr<TreeNodeW> child);
    void addParent(TreeNodeW* parent_node);

    void removeNode();
    bool isRoot();
    void uncheckParentNodes();

    virtual std::unique_ptr<TreeNodeW> makeTreeNodeWidget(ITreeNode* node);

  protected:
    Wt::WContainerWidget* header_container_;
    Wt::WPushButton* options_button_;
    Wt::WHBoxLayout* node_block_;
    Wt::WContainerWidget* check_box_container;
    Wt::WCheckBox* check_box_;
    TreeNodeW* parent_;
    ITreeNode* node_;
    std::unique_ptr<Wt::WPopupWidget> tool_tip_;

  private:
    std::unique_ptr<Wt::WContainerWidget> fillToolTipContainer(
        std::unique_ptr<Wt::WContainerWidget> content, std::string description,
        std::vector<std::string> tags);
    void addToolTip(std::unique_ptr<Wt::WContainerWidget> content);  // переделать на теги Сени
};
