#include <gtest/gtest.h>

#include "IManagers.hpp"
#include "ITreeNode.hpp"
#include "Node.hpp"
#include "SessionScopeMap.hpp"
#include "TreeNode.hpp"
#include "User.hpp"

class SessionSuit : public ::testing::Test {
protected:
	void SetUp() override {
		managers = SessionScopeMap::instance().get()->managers();
	}

	void TearDown() override {
		SessionScopeMap::instance().remove();
	}

	IManagers* managers;
};

TEST_F(SessionSuit, TreeNodeCreation) {
	UserSptr user = managers->user_manager()->get();
	NodeSptr node = managers->node_manager()->get(user->root_id);

	EXPECT_NO_THROW((TreeNode(*node)));
}

TEST_F(SessionSuit, TreeNodeGettingChilds) {
	UserSptr user = managers->user_manager()->get();
	NodeSptr node = managers->node_manager()->get(user->root_id);

	TreeNode tree_node(*node);

	std::vector<Node> expected_children = {
		Node(3, 1, 3, 0, PRIVATE_GROUP),
		Node(4, 1, 4, 0, PUBLIC_GROUP),
		Node(5, 1, 5, 0, SUBSCRIPTIONS_GROUP),
		Node(6, 1, 6, 0, PROFILE_GROUP)
	};

	std::vector<ITreeNode*> got_children = tree_node.getChildren();

	auto e = expected_children.begin();
	auto g = got_children.begin();

	for (; e != expected_children.end() && g != got_children.end(); e++, g++) {
		EXPECT_EQ(e->id, (*g)->getNode().id);
		EXPECT_EQ(e->parent_id, (*g)->getNode().parent_id);
		EXPECT_EQ(e->resource_id, (*g)->getNode().resource_id);
		EXPECT_EQ(e->type, (*g)->getNode().type);
	}
}

TEST_F(SessionSuit, TreeNodeRemovingChild) {
	UserSptr user = managers->user_manager()->get();
	NodeSptr node = managers->node_manager()->get(user->root_id);

	TreeNode tree_node(*node);

	std::vector<ITreeNode*> children = tree_node.getChildren();
	std::vector<ITreeNode*> children1 = children[0]->getChildren();

	EXPECT_NO_THROW(children1[0]->remove());
	EXPECT_NO_THROW(children1[1]->remove());
	EXPECT_NO_THROW(children[0]->remove());
	EXPECT_NO_THROW(children[1]->remove());
	EXPECT_NO_THROW(children[2]->remove());
	EXPECT_NO_THROW(children[3]->remove());
}

TEST_F(SessionSuit, TreeNodeAdditionChild) {
	UserSptr user = managers->user_manager()->get();
	NodeSptr node = managers->node_manager()->get(user->root_id);
	
	TreeNode tree_node(*node);

	std::vector<ITreeNode*> children = tree_node.getChildren();
	std::vector<ITreeNode*> children1 = children[1]->getChildren();

	EXPECT_NO_THROW(tree_node.addChild(children1[0]->getNode()));

	std::vector<ITreeNode*> expected_children = children1[0]->getChildren();
	std::vector<ITreeNode*> got_children = tree_node.getChildren().back()->getChildren();

	for (auto e = expected_children.begin(), g = got_children.begin();
		e != expected_children.end() && g != got_children.end();
		e++, g++) {

		EXPECT_EQ((*e)->getNode().id, (*g)->getNode().id);
		EXPECT_EQ((*e)->getNode().parent_id, (*g)->getNode().parent_id);
		EXPECT_EQ((*e)->getNode().resource_id, (*g)->getNode().resource_id);
		EXPECT_EQ((*e)->getNode().type, (*g)->getNode().type);
	}
}

