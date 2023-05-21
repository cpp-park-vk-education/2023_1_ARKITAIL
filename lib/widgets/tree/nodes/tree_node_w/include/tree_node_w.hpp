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
#include "tree_node_dir_w_builder.hpp"
#include "tree_node_leaf_w_builder.hpp"
#include "tree_node_other_dir_w_builder.hpp"
#include "tree_node_sub_dir_w_builder.hpp"
#include "tree_node_w_builder_base.hpp"

class TreeNodeW : public Wt::WContainerWidget {
    friend class TreeNodeWBuilderBase;
    friend class TreeNodeLeafWBuilder;
    friend class TreeNodeDirWBuilder;
    friend class TreeNodeOtherDirWBuilder;
    friend class TreeNodeSubDirWBuilder;

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

    virtual std::unique_ptr<TreeNodeW> makeTreeNodeWidget(ITreeNode* node);
    void setOptions(std::unique_ptr<OptionsW> options);
    TreeNodeW* addOptions(std::unique_ptr<OptionsW> options);
    TreeNodeW* addToolTip(std::string description, std::vector<std::string> tags);
    TreeNodeW* addToolTip(std::string description, std::vector<std::string> tags, User author);
    TreeNodeW* addHead(std::unique_ptr<Wt::WWidget>);
    TreeNodeW* addCheckBox();
    TreeNodeW* endNode();

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
