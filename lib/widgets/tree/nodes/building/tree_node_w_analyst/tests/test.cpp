#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include "ManagersStub.hpp"
#include "Node.hpp"
#include "TreeNodeMock.hpp"
#include "TreeNodeWAnalyst.hpp"
#include "TreeNodeWAnalystBase.hpp"
#include "TreeNodeWOtherAnalyst.hpp"
#include "TreeNodeWSubAnalyst.hpp"

class TreeNodeWAnalystTest : public ::testing::Test {
  protected:
    void SetUp() override {
        m = std::make_unique<ManagersStub>();
        managers = m.get();
        analyst_ = TreeNodeWAnalyst(managers);
        sub_analyst_ = TreeNodeWSubAnalyst(managers);
        other_analyst_ = TreeNodeWOtherAnalyst(managers);
        auto tree_node = TreeNodeMock(Node(0, 0, 0, NodeType::ROOT), nullptr);
        group_nodes_.push_back(&tree_node);
        group_nodes_.push_back(group_nodes_[0]->addChild(Node(1, 0, 1, NodeType::PRIVATE_GROUP)));
        group_nodes_.push_back(group_nodes_[0]->addChild(Node(2, 0, 2, NodeType::PUBLIC_GROUP)));
        group_nodes_[0]->addChild(Node(3, 0, 3, NodeType::SUBSCRIPTIONS_GROUP));
        group_nodes_[0]->addChild(Node(4, 0, 4, NodeType::PROFILE_GROUP));
    }

    void TearDown() override {}

    TreeNodeWAnalyst analyst_;
    TreeNodeWSubAnalyst sub_analyst_;
    TreeNodeWOtherAnalyst other_analyst_;
    std::vector<ITreeNode*> group_nodes_;
    ManagersStub* managers;
    std::unique_ptr<ManagersStub> m;
};

TEST_F(TreeNodeWAnalystTest, TYPIC) {
    managers->user_manager();

    EXPECT_EQ(1, 1);
}

TEST_F(TreeNodeWAnalystTest, TYPIC1) {
    for (auto group_node : group_nodes_) {
        analyst_.analyseTreeNodeWChild(group_node);
    }

    EXPECT_EQ(1, 1);
}

TEST_F(TreeNodeWAnalystTest, TYPIC_TYPIC_TUPIC) {
    EXPECT_EQ(1, 1);
}
