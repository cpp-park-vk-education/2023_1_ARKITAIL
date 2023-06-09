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

#define EXPECT_TAGS_EQ(tags1, tags2)                                                          \
    {                                                                                         \
        EXPECT_EQ(tags1.size(), tags2.size())                                                 \
            << "Tags vectors of root_data and test_data are of unequal length";               \
        if (tags1.size() == tags2.size()) {                                                   \
            for (size_t i = 0; i < tags1.size(); ++i) {                                       \
                EXPECT_EQ(tags1[i], tags2[i])                                                 \
                    << "Tags vectors of root_data and test_data differ at index " << i        \
                    << "\nExpected: {" << tags2[i].id << ", " << tags2[i].name << "}\nGot: {" \
                    << tags1[i].id << ", " << tags1[i].name << '}';                           \
            }                                                                                 \
        }                                                                                     \
    }

#define EXPECT_CONVERTED_DATA_EQ(data1, data2)                 \
    {                                                          \
        EXPECT_EQ(data1.components_set, data2.components_set); \
        EXPECT_EQ(data1.name, data2.name);                     \
        EXPECT_TAGS_EQ(data1.tags, data2.tags);                \
        EXPECT_EQ(data1.description, data2.description);       \
        EXPECT_EQ(data1.author, data2.author);                 \
        EXPECT_EQ(data1.tree_node, data2.tree_node);           \
    }

class AnalystBaseTest : public ::testing::Test {
  protected:
    void SetUp() override {
        managers_ = std::make_unique<ManagersStub>();
        // tree
        root_ = std::make_unique<TreeNodeMock>(Node(0, 0, 0, 0, NodeType::ROOT));

        // PRIVATE
        group_options_nodes_.push_back(root_->addChild(Node(1, 0, 1, 0, NodeType::PRIVATE_GROUP)));

        // PUBLIC
        group_options_nodes_.push_back(root_->addChild(Node(2, 0, 2, 0, NodeType::PUBLIC_GROUP)));

        // SUBSCRIPTIONS
        group_nodes_.push_back(root_->addChild(Node(3, 0, 3, 0, NodeType::SUBSCRIPTIONS_GROUP)));
        sub_dir_options_node_ =
            group_nodes_[0]->addChild(Node(9, 3, 9, 0, NodeType::PUBLIC_DIRECTORY));

        // PROFILE
        group_nodes_.push_back(root_->addChild(Node(4, 0, 4, 0, NodeType::PROFILE_GROUP)));
    }

    void TearDown() override {}

    std::unique_ptr<IManagers> managers_;

    std::unique_ptr<TreeNodeWAnalystBase> analyst_;

    std::unique_ptr<ITreeNode> root_;
    std::vector<ITreeNode*> group_nodes_;
    std::vector<ITreeNode*> group_options_nodes_;
    ITreeNode* sub_dir_options_node_;
};

class TreeNodeWAnalystTest : public AnalystBaseTest {
  protected:
    void SetUp() override {
        AnalystBaseTest::SetUp();
        analyst_ = std::make_unique<TreeNodeWAnalyst>(managers_.get());
        // PRIVATE DIR
        private_dir_nodes_.push_back(
            group_options_nodes_[0]->addChild(Node(5, 1, 5, 0, NodeType::PRIVATE_DIRECTORY)));
        private_dir_nodes_.push_back(
            private_dir_nodes_[0]->addChild(Node(6, 5, 6, 0, NodeType::PRIVATE_DIRECTORY)));
        // PRIVATE CALENDAR
        private_calendar_nodes_.push_back(
            group_options_nodes_[0]->addChild(Node(12, 1, 0, 0, NodeType::PRIVATE_CALENDAR)));
        private_calendar_nodes_.push_back(
            private_dir_nodes_[0]->addChild(Node(13, 5, 1, 0, NodeType::PRIVATE_CALENDAR)));

        // PUBLIC DIR
        public_dir_nodes_.push_back(
            group_options_nodes_[1]->addChild(Node(7, 2, 7, 0, NodeType::PUBLIC_DIRECTORY)));
        public_dir_nodes_.push_back(
            public_dir_nodes_[0]->addChild(Node(8, 7, 8, 0, NodeType::PUBLIC_DIRECTORY)));
        // PUBLIC CALENDAR
        public_calendar_nodes_.push_back(
            group_options_nodes_[1]->addChild(Node(14, 2, 3, 0, NodeType::PUBLIC_CALENDAR)));
        public_calendar_nodes_.push_back(
            public_dir_nodes_[0]->addChild(Node(15, 7, 4, 0, NodeType::PUBLIC_CALENDAR)));

        // SUB OPTIONS CALENDAR
        sub_calendar_options_node_ = group_nodes_[0]->addChild(Node(16, 3, 5, 0, NodeType::PUBLIC_CALENDAR));
        // PROFILE
    
    }

    std::vector<ITreeNode*> private_dir_nodes_;
    std::vector<ITreeNode*> private_calendar_nodes_;
    std::vector<ITreeNode*> public_dir_nodes_;
    std::vector<ITreeNode*> public_calendar_nodes_;
    ITreeNode* sub_calendar_options_node_;
};

class TreeNodeWSubAnalystTest : public AnalystBaseTest {
  protected:
    void SetUp() override {
        AnalystBaseTest::SetUp();
        analyst_ = std::make_unique<TreeNodeWSubAnalyst>(managers_.get());
        sub_dir_nodes_.push_back(
            sub_dir_options_node_->addChild(Node(10, 9, 10, 0, NodeType::PUBLIC_DIRECTORY)));
        sub_dir_nodes_.push_back(
            sub_dir_nodes_[0]->addChild(Node(11, 10, 11, 0, NodeType::PUBLIC_DIRECTORY)));
        
        sub_calendar_nodes_.push_back(
            sub_dir_options_node_->addChild(Node(17, 9, 6, 0, NodeType::PUBLIC_CALENDAR)));
        sub_calendar_nodes_.push_back(
            sub_dir_nodes_[0]->addChild(Node(18, 10, 7, 0, NodeType::PUBLIC_CALENDAR)));
    }
    std::vector<ITreeNode*> sub_dir_nodes_;
    std::vector<ITreeNode*> sub_calendar_nodes_;
};

class TreeNodeWOtherAnalystTest : public AnalystBaseTest {
  protected:
    void SetUp() override {
        AnalystBaseTest::SetUp();
        analyst_ = std::make_unique<TreeNodeWOtherAnalyst>(managers_.get());
        other_root_dir_node_ = group_options_nodes_[1]->addChild(Node(19, 2, 12, 0, NodeType::PUBLIC_DIRECTORY));
        other_dir_node_.push_back(other_root_dir_node_->addChild(Node(20, 19, 13, 0, NodeType::PUBLIC_DIRECTORY)));
        other_dir_node_.push_back(other_dir_node_[0]->addChild(Node(21, 20, 14, 0, NodeType::PUBLIC_DIRECTORY)));
        other_root_calendar_node_ = group_options_nodes_[1]->addChild(Node(22, 2, 8, 0, NodeType::PUBLIC_CALENDAR));
        other_calendar_node_ = other_dir_node_[0]->addChild(Node(23, 20, 9, 0, NodeType::PUBLIC_CALENDAR));

    }
    ITreeNode* other_root_dir_node_;
    std::vector<ITreeNode*> other_dir_node_;
    ITreeNode* other_root_calendar_node_;
    ITreeNode* other_calendar_node_;

};

TEST_F(TreeNodeWAnalystTest, RootGroup) {
    TreeNodeWConvertedData root_data = analyst_->analyseTreeNodeWChild(root_.get());
    TreeNodeWConvertedData test_root_data =
        TreeNodeWConvertedData{TreeNodeWType::GROUP,
                               "testRoot",
                               "root desc",
                               std::vector<Tag>{},
                               User(0, 0, "login", "email", "nickname", "desc"),
                               root_.get()};

    EXPECT_CONVERTED_DATA_EQ(root_data, test_root_data);
}

TEST_F(TreeNodeWAnalystTest, GroupOptions) {
    TreeNodeWConvertedData private_group_data =
        analyst_->analyseTreeNodeWChild(group_options_nodes_[0]);
    TreeNodeWConvertedData test_private_group_data =
        TreeNodeWConvertedData{TreeNodeWType::GROUP_OPTIONS,
                               "testPrivateGroup",
                               "testPrivateGroup desc",
                               std::vector<Tag>{},
                               User(0, 0, "login", "email", "nickname", "desc"),
                               group_options_nodes_[0]};
    EXPECT_CONVERTED_DATA_EQ(private_group_data, test_private_group_data);

    TreeNodeWConvertedData public_group_data =
        analyst_->analyseTreeNodeWChild(group_options_nodes_[1]);
    TreeNodeWConvertedData test_public_group_data =
        TreeNodeWConvertedData{TreeNodeWType::GROUP_OPTIONS,
                               "testPublicGroup",
                               "testPublicGroup desc",
                               std::vector<Tag>{},
                               User(0, 0, "login", "email", "nickname", "desc"),
                               group_options_nodes_[1]};
    EXPECT_CONVERTED_DATA_EQ(public_group_data, test_public_group_data);
}

TEST_F(TreeNodeWAnalystTest, Group) {
    TreeNodeWConvertedData private_group_data = analyst_->analyseTreeNodeWChild(group_nodes_[0]);
    TreeNodeWConvertedData test_private_group_data =
        TreeNodeWConvertedData{TreeNodeWType::GROUP,
                               "testSubscriptionsGroup",
                               "testSubscriptionsGroup desc",
                               std::vector<Tag>{},
                               User(0, 0, "login", "email", "nickname", "desc"),
                               group_nodes_[0]};
    EXPECT_CONVERTED_DATA_EQ(private_group_data, test_private_group_data);

    TreeNodeWConvertedData public_group_data = analyst_->analyseTreeNodeWChild(group_nodes_[1]);
    TreeNodeWConvertedData test_public_group_data =
        TreeNodeWConvertedData{TreeNodeWType::GROUP,
                               "testProfileGroup",
                               "testProfileGroup desc",
                               std::vector<Tag>{},
                               User(0, 0, "login", "email", "nickname", "desc"),
                               group_nodes_[1]};
    EXPECT_CONVERTED_DATA_EQ(public_group_data, test_public_group_data);
}

TEST_F(TreeNodeWAnalystTest, PrivateDir) {
    for (auto private_dir : private_dir_nodes_) {
        TreeNodeWConvertedData private_dir_data = analyst_->analyseTreeNodeWChild(private_dir);
        TreeNodeWConvertedData test_private_dir_data =
            TreeNodeWConvertedData{TreeNodeWType::DIR,
                                   "testPrivateDir",
                                   "testPrivateDir desc",
                                   std::vector<Tag>{},
                                   User(0, 0, "login", "email", "nickname", "desc"),
                                   private_dir};
        EXPECT_CONVERTED_DATA_EQ(private_dir_data, test_private_dir_data);
    }
}

TEST_F(TreeNodeWAnalystTest, PrivateCalendar) {
    for (auto private_calendar : private_calendar_nodes_) {
        TreeNodeWConvertedData private_calendar_data = analyst_->analyseTreeNodeWChild(private_calendar);
        TreeNodeWConvertedData test_private_calendar_data =
            TreeNodeWConvertedData{TreeNodeWType::PERSONAL_CALENDAR,
                                   "PrivateCalendar",
                                   "PrivateCalendar desc",
                                   std::vector<Tag>{},
                                   User(0, 0, "login", "email", "nickname", "desc"),
                                   private_calendar};
        EXPECT_CONVERTED_DATA_EQ(private_calendar_data, test_private_calendar_data);
    }
}

TEST_F(TreeNodeWAnalystTest, PublicDir) {
    for (auto public_dir : public_dir_nodes_) {
        TreeNodeWConvertedData public_dir_data = analyst_->analyseTreeNodeWChild(public_dir);
        TreeNodeWConvertedData test_public_dir_data =
            TreeNodeWConvertedData{TreeNodeWType::DIR,
                                   "testPublicDir",
                                   "testPublicDir desc",
                                   std::vector<Tag>{},
                                   User(0, 0, "login", "email", "nickname", "desc"),
                                   public_dir};
        EXPECT_CONVERTED_DATA_EQ(public_dir_data, test_public_dir_data);
    }
}

TEST_F(TreeNodeWAnalystTest, PublicCalendar) {
    for (auto public_calendar : public_calendar_nodes_) {
        TreeNodeWConvertedData public_calendar_data = analyst_->analyseTreeNodeWChild(public_calendar);
        TreeNodeWConvertedData test_public_calendar_data =
            TreeNodeWConvertedData{TreeNodeWType::PERSONAL_CALENDAR,
                                   "PublicCalendar",
                                   "PublicCalendar desc",
                                   std::vector<Tag>{},
                                   User(0, 0, "login", "email", "nickname", "desc"),
                                   public_calendar};
        EXPECT_CONVERTED_DATA_EQ(public_calendar_data, test_public_calendar_data);
    }
}

TEST_F(TreeNodeWAnalystTest, SubDirOptions) {
    TreeNodeWConvertedData sub_dir_options_data =
        analyst_->analyseTreeNodeWChild(sub_dir_options_node_);
    TreeNodeWConvertedData test_sub_dir_options_data =
        TreeNodeWConvertedData{TreeNodeWType::SUB_DIR_OPTIONS,
                               "testSubMountDir",
                               "testSubMountDir desc",
                               std::vector<Tag>{},
                               User(0, 0, "login", "email", "nickname", "desc"),
                               sub_dir_options_node_};

    EXPECT_CONVERTED_DATA_EQ(sub_dir_options_data, test_sub_dir_options_data);
}

TEST_F(TreeNodeWAnalystTest, SubCalendarOptions) {
    TreeNodeWConvertedData sub_calendar_options_data =
        analyst_->analyseTreeNodeWChild(sub_calendar_options_node_);
    TreeNodeWConvertedData test_sub_calendar_options_data =
        TreeNodeWConvertedData{TreeNodeWType::SUB_CALENDAR_OPTIONS,
                               "testSubMountCalendar",
                               "testSubMountCalendar desc",
                               std::vector<Tag>{},
                               User(0, 0, "login", "email", "nickname", "desc"),
                               sub_calendar_options_node_};

    EXPECT_CONVERTED_DATA_EQ(sub_calendar_options_data, test_sub_calendar_options_data);
}

TEST_F(TreeNodeWSubAnalystTest, SubDir) {
    for (auto sub_dir : sub_dir_nodes_) {
        TreeNodeWConvertedData sub_dir_data = analyst_->analyseTreeNodeWChild(sub_dir);
        TreeNodeWConvertedData test_sub_dir_data =
            TreeNodeWConvertedData{TreeNodeWType::SUB_DIR,
                                   "testSubDir",
                                   "testSubDir desc",
                                   std::vector<Tag>{},
                                   User(0, 0, "login", "email", "nickname", "desc"),
                                   sub_dir};
        EXPECT_CONVERTED_DATA_EQ(sub_dir_data, test_sub_dir_data);
    }
}

TEST_F(TreeNodeWSubAnalystTest, SubCalendar) {
    for (auto sub_calendar : sub_calendar_nodes_) {
        TreeNodeWConvertedData sub_calendar_data = analyst_->analyseTreeNodeWChild(sub_calendar);
        TreeNodeWConvertedData test_sub_calendar_data =
            TreeNodeWConvertedData{TreeNodeWType::SUB_CALENDAR,
                                   "testSubCalendar",
                                   "testSubCalendar desc",
                                   std::vector<Tag>{},
                                   User(0, 0, "login", "email", "nickname", "desc"),
                                   sub_calendar};
        EXPECT_CONVERTED_DATA_EQ(sub_calendar_data, test_sub_calendar_data);
    }
}

TEST_F(TreeNodeWOtherAnalystTest, DISABLED_OtherRootGroupSub) {
}

TEST_F(TreeNodeWOtherAnalystTest, DISABLED_OtherRootGroupUnsub) {
}

TEST_F(TreeNodeWOtherAnalystTest, DISABLED_OtherRootDirSub) {
}

TEST_F(TreeNodeWOtherAnalystTest, DISABLED_OtherRootDirUnsub) {
}

TEST_F(TreeNodeWOtherAnalystTest, DISABLED_OtherRootCalendarSub) {
}

TEST_F(TreeNodeWOtherAnalystTest, DISABLED_OtherRootCalendarUnsub) {
}

TEST_F(TreeNodeWOtherAnalystTest, DISABLED_OtherDirSub) {
}

TEST_F(TreeNodeWOtherAnalystTest, DISABLED_OtherDirUnsub) {
}

TEST_F(TreeNodeWOtherAnalystTest, DISABLED_OtherCalendarSub) {
}

TEST_F(TreeNodeWOtherAnalystTest, DISABLED_OtherCalendarUnsub) {
}
