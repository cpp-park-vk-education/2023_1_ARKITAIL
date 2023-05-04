#pragma once

#include <Wt/WIconPair.h>
#include <Wt/WText.h>

#include <memory>
#include <string>

#include "TreeNodeW.hpp"

class TreeNodeDirW : public TreeNodeW {
  public:
    TreeNodeDirW(int id, std::string label);
    ~TreeNodeDirW() = default;
    void showChildNodes();
    void closeChildNodes();
    Wt::TreeNodeW* addChildNode(std::unique_ptr<TreeNodeW>);
    std::vector<TreeNodeW*> childNodes();
    bool isSelected();

  private:
    Wt::WIconPair* icon_;
    Wt::WText* label_;
};
