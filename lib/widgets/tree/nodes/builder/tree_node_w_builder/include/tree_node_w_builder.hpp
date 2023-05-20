#pragma once

#include <memory>

#include "ITreeNode.hpp"
#include "User.hpp"
#include "options_w.hpp"

class TreeNodeW;

//   Разделить на несколько билдеров
//  1) Разные опции
//  2) Разные типы нод
//  3) Разные туллтипы
//  4) Разные заголовки
//

class TreeNodeWBuilder {
  protected:
    std::unique_ptr<TreeNodeW> tree_node_w;

  public:
    TreeNodeWBuilder();
    TreeNodeWBuilder* createTreeNodeDirW(ITreeNode* node);
    TreeNodeWBuilder* createTreeNodeLeafW(ITreeNode* node);
    TreeNodeWBuilder* createTreeNodeOtherDirW(ITreeNode* node);
    TreeNodeWBuilder* createTreeNodeSubscriptionsDirW(ITreeNode* node);

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
