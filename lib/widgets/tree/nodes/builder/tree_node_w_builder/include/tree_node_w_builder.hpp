#pragma once

#include <memory>

#include "ITreeNode.hpp"
#include "User.hpp"
#include "options_w.hpp"

class TreeNodeW;

class TreeNodeWBuilder {
  protected:
    std::unique_ptr<TreeNodeW> tree_node_w_;

  public:
    TreeNodeWBuilder();
    TreeNodeWBuilder(std::unique_ptr<TreeNodeW> tree_node_w);
    ~TreeNodeWBuilder() = default;

    TreeNodeWBuilder* addHead(std::unique_ptr<Wt::WWidget> head);
    TreeNodeWBuilder* addCheckBox();
    TreeNodeWBuilder* addOptions(std::unique_ptr<OptionsW> options);

    TreeNodeWBuilder* addToolTip(std::string description, std::vector<std::string> tags);
    TreeNodeWBuilder* addToolTip(std::string description, std::vector<std::string> tags,
                                 User author);
    TreeNodeWBuilder* addParent(TreeNodeW* parent_node);
    TreeNodeWBuilder* endNode();

    std::unique_ptr<TreeNodeW> getTreeNodeW();

  private:
    std::unique_ptr<Wt::WContainerWidget> fillToolTipContainer(
        std::unique_ptr<Wt::WContainerWidget> content, std::string description,
        std::vector<std::string> tags);
    void addToolTip(std::unique_ptr<Wt::WContainerWidget> content);
};
