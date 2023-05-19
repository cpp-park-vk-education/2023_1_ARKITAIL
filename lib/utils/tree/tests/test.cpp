#include <gtest/gtest.h>

#include "TreeNode.hpp"
#include "Tree.hpp"
#include "Node.hpp"
/*

TEST(TreeTests, DISABLED_Creation) {
    Node n(0, 0, 0, NodeType::PUBLIC_CALENDAR);
    EXPECT_NO_THROW(Tree t(n));
}

TEST(TreeNodeTests, DISABLED_Insertion) {
    Node n(0, 0, 0, NodeType::);
    Tree t(n);

    t.getRoot()->addChild(std::unique_ptr<TreeNode> tree_node)

    auto childs = t.getRoot()->getChilds();

    EXPECT_EQ(childs.size(), 1);

    EXPECT_EQ(childs[0]->getNode().id, n.id);
    EXPECT_EQ(childs[0]->getNode().parent_id, n.parent_id);
    EXPECT_EQ(childs[0]->getNode().resource_id, n.resource_id);
    EXPECT_EQ(childs[0]->getNode().type, n.type);
}

TEST(TreeNodeTests, DISABLED_Deletion) {
    Node n(0, 0, 0, NodeType::CALENDAR);
    TreeNode tn(n);
    Tree t(n);

    t.insertNode(tn, t.getRoot());
    auto childs = t.getRoot()->getChilds();

    t.removeNode(childs[0]);
    childs = t.getRoot()->getChilds();

    EXPECT_EQ(childs.size(), 0);
}

TEST(TreeNodeTests, DISABLED_Creation) {
    Node n(0, 0, 0, NodeType::CALENDAR);
    EXPECT_NO_THROW(TreeNode tn(n));
}

TEST(TreeNodeTests, DISABLED_Checking) {
    Node n(0, 0, 0, NodeType::CALENDAR);
    TreeNode tn(n);

    EXPECT_FALSE(tn.isChecked());
    tn.check();
    EXPECT_TRUE(tn.isChecked());
}

TEST(TreeNodeTests, DISABLED_Childs) {
    Node n(0, 0, 0, NodeType::CALENDAR);
    TreeNode tn(n);

    auto childs = tn.getChilds();
    EXPECT_EQ(childs.size(), 0);
}

*/

