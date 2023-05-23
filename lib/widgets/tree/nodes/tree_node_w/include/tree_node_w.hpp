#pragma once

#include <Wt/WCheckBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WPopupWidget.h>

#include <memory>

#include "Calendar.hpp"
#include "Directory.hpp"
#include "ITreeNode.hpp"
#include "ITreeNodeWAnalyst.hpp"
#include "Node.hpp"
#include "Tree.hpp"
#include "TreeNodeWBuilderBase.hpp"
#include "User.hpp"
#include "options_w.hpp"

class TreeNodeW : public Wt::WContainerWidget {
    friend class TreeNodeWBuilderBase;

  public:
    TreeNodeW();
    TreeNodeW(ITreeNode* node);
    virtual ~TreeNodeW() = default;
    virtual void checkNode();
    virtual void uncheckNode();
    virtual void showNode();
    virtual void closeNode();
    virtual void performAction(Action action);

    virtual TreeNodeW* addChildNode(std::unique_ptr<TreeNodeW> child);
    TreeNodeW* addParent(TreeNodeW* parent_node);

    void removeNode();
    bool isRoot();
    bool isCanCheck();
    void uncheckParentNodes();
    NodeType getType();

    std::unique_ptr<TreeNodeW> makeTreeNodeWidget(ITreeNode* node);
    void setOptions(std::unique_ptr<OptionsW> options);
    void addToolTipSignal();

  protected:
    std::unique_ptr<ITreeNodeWAnalyst> analyst_;
    Wt::WContainerWidget* header_container_;
    Wt::WPushButton* options_button_;
    Wt::WHBoxLayout* node_block_;
    Wt::WContainerWidget* check_box_container;
    Wt::WCheckBox* check_box_;
    TreeNodeW* parent_;
    ITreeNode* node_;
    std::unique_ptr<Wt::WPopupWidget> tool_tip_;
};
