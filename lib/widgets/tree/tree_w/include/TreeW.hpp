#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>

#include <vector>

#include "AddProfileW.hpp"
#include "Event.hpp"
#include "Node.hpp"
#include "Tree.hpp"
#include "TreeNode.hpp"
#include "TreeNodeW.hpp"

class TreeW : public Wt::WContainerWidget {
  public:
    TreeW();
    ~TreeW() = default;
    void setRoot(const Node& node);
    void setRoot(const Node& node, const User& user);
    void checkNode(TreeNodeW* tree_node_w);
    void getRangeEvents(Wt::WDate date1, Wt::WDate date2);
    std::vector<size_t> getCheckedNodes();
    void sendCheckedNodes();

    Wt::Signal<> node_checked;
    Wt::Signal<Wt::WDate, std::vector<Event>> events_getted;

  private:
    std::unique_ptr<Tree> tree_manager_;
    Wt::WContainerWidget* header_;
    AddProfileW* add_profile_w_;
    TreeNodeW* root_;

};
