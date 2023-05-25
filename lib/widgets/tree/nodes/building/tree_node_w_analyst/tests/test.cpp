#include <gtest/gtest.h>

#include <memory>

#include "TreeNodeMock.hpp"
#include "TreeNodeWAnalyst.hpp"
#include "TreeNodeWOtherAnalyst.hpp"
#include "TreeNodeWSubAnalyst.hpp"

class TreeNodeWAnalystTest : public ::testing::Test {
  protected:
    void SetUp() override {
        tree_node_ = std::make_unique<TreeNodeMock>();
    }

    void TearDown() override {}

    std::unique_ptr<TreeNodeMock> tree_node_;

    std::unique_ptr<ITreeNodeWAnalyst> analyst_;
};
