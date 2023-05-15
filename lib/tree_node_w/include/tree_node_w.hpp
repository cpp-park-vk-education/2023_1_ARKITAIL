#pragma once

#include <Wt/WCheckBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WPopupWidget.h>

#include <vector>

#include "Node.hpp"
#include "Tree.hpp"
#include "TreeNode.hpp"
#include "options_w.hpp"

class TreeNodeW : public Wt::WContainerWidget {
  public:
    TreeNodeW();
    virtual ~TreeNodeW() = default;
    virtual void checkNode() = 0;
    virtual void uncheckNode() = 0;
    virtual void showNode() = 0;
    virtual void closeNode() = 0;

    virtual TreeNodeW* addChildNode(std::unique_ptr<TreeNodeW> child) { return child.get(); }
    void addParent(TreeNodeW* parent_node);

    void removeNode();
    bool isRoot();
    void uncheckParentNodes();
    virtual Wt::WInteractWidget* getTitle() = 0;

    TreeNodeW* addOptions(std::unique_ptr<OptionsW> options);
    TreeNodeW* addToolTip(std::string description, std::vector<std::string> tags);
    TreeNodeW* addToolTip(std::string description, std::vector<std::string> tags, std::string author);
    TreeNodeW* hideCheckBox();
    TreeNodeW* endNode();
    TreeNode* addNode(const Node& node);

  protected:
    Wt::WPushButton* options_button_;
    Wt::WHBoxLayout* node_block_;
    Wt::WCheckBox* check_box_;
    TreeNodeW* parent_;
    // Node& node_;
    std::unique_ptr<Wt::WPopupWidget> tool_tip_;

  private:
    std::unique_ptr<Wt::WContainerWidget> fillToolTipContainer(std::unique_ptr<Wt::WContainerWidget> content,
                                                               std::string description, std::vector<std::string> tags);
    void addToolTip(std::unique_ptr<Wt::WContainerWidget> content);  // переделать на теги Сени
};
