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
#include "OptionsW.hpp"
#include "Tree.hpp"
#include "TreeNodeWAnalystBase.hpp"
#include "TreeNodeWBuilderBase.hpp"
#include "User.hpp"

class TreeNodeW : public Wt::WContainerWidget {
    friend class TreeNodeWBuilderBase;

  public:
    TreeNodeW();
    TreeNodeW(ITreeNode* node);
    virtual ~TreeNodeW() = default;
    virtual void checkNode() = 0;
    virtual void uncheckNode() = 0;
    virtual void open();
    virtual void showNode();
    virtual void closeNode();
    virtual std::vector<TreeNodeW*> getChildrenNodes();
    virtual void performAction(Action action);

    virtual TreeNodeW* addChildNode(std::unique_ptr<TreeNodeW> child);
    TreeNodeW* addParent(TreeNodeW* parent_node);

    void removeNode();
    virtual void removeChildNode(TreeNodeW* child);
    bool isRoot();
    bool isCanCheck();
    bool isCheck();
    void uncheckParentNodes();
    NodeType getType();
    ITreeNode* getTreeNode();


    std::unique_ptr<TreeNodeW> makeTreeNodeWidget(ITreeNode* node);
    void setOptions(std::unique_ptr<OptionsW> options);
    void addToolTipSignal();

  protected:
    Wt::Signal<ITreeNode*> checked_;
    Wt::WText* text_title_;
    std::unique_ptr<TreeNodeWAnalystBase> analyst_;
    Wt::WContainerWidget* header_container_;
    Wt::WPushButton* options_button_;
    Wt::WHBoxLayout* node_block_;
    Wt::WContainerWidget* check_box_container;
    Wt::WCheckBox* check_box_;
    TreeNodeW* parent_;
    ITreeNode* node_;
    std::unique_ptr<Wt::WPopupWidget> tool_tip_;
};
