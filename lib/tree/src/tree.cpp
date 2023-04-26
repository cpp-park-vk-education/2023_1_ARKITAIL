#include "tree.hpp"

#include <Wt/WLineEdit.h>
#include <Wt/WText.h>
#include <Wt/WTree.h>
#include <Wt/WTreeNode.h>

#include <memory>

Tree::Tree() {
    auto search_ptr = std::make_unique<Wt::WLineEdit>();
    search = search_ptr.get();
    search->addStyleClass("ms-2");

    auto tree_ptr = std::make_unique<Wt::WTree>();
    tree = tree_ptr.get();
    tree->setSelectionMode(Wt::SelectionMode::Extended);
    tree->addStyleClass("treeview");

    auto rootPtr = std::make_unique<Wt::WTreeNode>("Tree root");
    rootPtr->addStyleClass("list-group");
    Wt::WTreeNode *rootTree = rootPtr.get();
    rootTree->setStyleClass("example-tree");
    tree->setTreeRoot(std::move(rootPtr));
    rootTree->label()->setTextFormat(Wt::TextFormat::Plain);
    rootTree->setLoadPolicy(Wt::ContentLoading::NextLevel);
    rootTree->addChildNode(std::make_unique<Wt::WTreeNode>("one"));
    rootTree->addChildNode(std::make_unique<Wt::WTreeNode>("two"));
    rootTree->decorationStyle();

    auto three = std::make_unique<Wt::WTreeNode>("three");
    three->addChildNode(std::make_unique<Wt::WTreeNode>("three: one"));
    three->addChildNode(std::make_unique<Wt::WTreeNode>("three: two"));
    rootTree->addChildNode(std::move(three));

    rootTree->expand();
    addWidget(std::move(search_ptr));
    addWidget(std::move(tree_ptr));
}
