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
#include "DbMock.hpp"
#include "IDbManagers.hpp"
#include "DbManagers.hpp"
#include "EventManager.hpp"
#include "UserDbManagerMock.hpp"
#include "NodeDbManagerMock.hpp"
#include "DirectoryDbManagerMock.hpp"
#include "CalendarDbManagerMock.hpp"
#include "EventDbManagerMock.hpp"
#include "CommentDbManagerMock.hpp"
#include "TagDbManagerMock.hpp"
#include "ProfileDbManagerMock.hpp"

#include "Managers.hpp"
#include "UserManager.hpp"
#include "NodeManager.hpp"
#include "DirectoryManager.hpp"
#include "CalendarManager.hpp"
#include "TagManager.hpp"
#include "ProfileManager.hpp"



class TreeNodeWAnalystTest : public ::testing::Test {
  protected:
    void SetUp() override {
        auto db = std::make_shared<DbMock>();
		
		auto db_managers = std::make_shared<DbManagers>(
			std::make_unique<UserDbManagerMock>(db),
			std::make_unique<NodeDbManagerMock>(db),
			std::make_unique<DirectoryDbManagerMock>(db),
			std::make_unique<CalendarDbManagerMock>(db),
			std::make_unique<EventDbManagerMock>(db),
			std::make_unique<CommentDbManagerMock>(),
			std::make_unique<TagDbManagerMock>(),
			std::make_unique<ProfileDbManagerMock>()
		);

		managers = std::make_unique<Managers>(
			std::make_unique<UserManager>(db_managers),
			std::make_unique<NodeManager>(db_managers),
			std::make_unique<DirectoryManager>(db_managers),
			std::make_unique<CalendarManager>(db_managers),
			std::make_unique<EventManager>(db_managers),
			std::make_unique<TagManager>(db_managers),
			std::make_unique<ProfileManager>(db_managers)
		);

        analyst_ = TreeNodeWAnalyst(managers.get());
        sub_analyst_ = TreeNodeWSubAnalyst(managers.get());
        other_analyst_ = TreeNodeWOtherAnalyst(managers.get());
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
    std::unique_ptr<IManagers> managers;
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
    for (auto group_node : group_nodes_) {
        group_node->getNode();
    }
    EXPECT_EQ(1, 1);
}
