#include <gtest/gtest.h>

#include "DbMock.hpp"
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
#include "ProfileManager.hpp"

#include "User.hpp"
#include "Node.hpp"

static void operator==(const Node& lhs, const Node& rhs) {
	EXPECT_EQ(lhs.id, rhs.id);
	EXPECT_EQ(lhs.parent_id, rhs.parent_id);
	EXPECT_EQ(lhs.resource_id, rhs.resource_id);
	EXPECT_EQ(lhs.type, rhs.type);
}

class ManagersSuit : public ::testing::Test {
protected:
	void SetUp() override {
		db = std::make_shared<DbMock>();
		
		db_managers = std::make_shared<DbManagers>(
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
			std::make_unique<ProfileManager>(db_managers)
		);

	}

	void TearDown() override {}

	std::shared_ptr<DbMock> db;
	std::shared_ptr<IDbManagers> db_managers;
	std::unique_ptr<IManagers> managers;

};

TEST_F(ManagersSuit, GetRootNodeOfCurrentUser) {
	auto user = managers->user_manager()->get();

	Node expected = {1, 1, 1, NodeType::ROOT};
	auto got = managers->node_manager()->get(user->root_id);
	
	EXPECT_EQ(expected.id, got->id);
	EXPECT_EQ(expected.parent_id, got->parent_id);
	EXPECT_EQ(expected.resource_id, got->resource_id);
	EXPECT_EQ(expected.type, got->type);
}

TEST_F(ManagersSuit, GetChildrens) {
	auto user = managers->user_manager()->get();
	
	std::vector<Node> expected = {
		Node(3, 1, 3, NodeType::PRIVATE_GROUP),
		Node(4, 1, 4, NodeType::PUBLIC_GROUP),
		Node(5, 1, 5, NodeType::SUBSCRIPTIONS_GROUP),
		Node(6, 1, 6, NodeType::PROFILE_GROUP)
	};

	auto root_node = managers->node_manager()->get(user->root_id);
	auto got = managers->node_manager()->getChildren(root_node->id);

	EXPECT_FALSE(got.empty());

	for (auto e = expected.begin(), g = got.begin(); e != expected.end() && g != got.end(); e++, g++)
		*e == *g;
}

// Разрешено
// Проверить добавление невалидных нод
TEST_F(ManagersSuit, AddNodeToCurrentUser) {
	auto user = managers->user_manager()->get();

	Node new_node = {
		0,
		3,
		0,
		PRIVATE_DIRECTORY
	};

	new_node.id = managers->node_manager()->add(
      std::make_shared<Node>(std::move(new_node)));
	EXPECT_NE(new_node.id, 0);
}

// Запрещено
TEST_F(ManagersSuit, AddNodeToOthrerUser) {
	auto user = managers->user_manager()->get();

	Node new_node = {
		0,
		15,
		0,
		PRIVATE_DIRECTORY
	};

	size_t new_node_id = managers->node_manager()->add(
      std::make_shared<Node>(std::move(new_node)));
	EXPECT_EQ(new_node_id, 0);
}

TEST_F(ManagersSuit, UpdateNodeForCurrentUser) {}
TEST_F(ManagersSuit, UpdareNodeForOtherUser) {}

TEST_F(ManagersSuit, RemoveNodeFromCurrentUser) {}
TEST_F(ManagersSuit, RemoveNodeFromOtherUser) {}

TEST_F(ManagersSuit, DISABLED_TagNode) {}

TEST_F(ManagersSuit, MoveNodeInsideUserTree) {}
TEST_F(ManagersSuit, MoveNodeBetweenUserTrees) {}

TEST_F(ManagersSuit, SubscribeToPublic) {}
TEST_F(ManagersSuit, SubscribeToPrivate) {}

TEST_F(ManagersSuit, Unsubscribe) {}

TEST_F(ManagersSuit, GetChildren) {}

