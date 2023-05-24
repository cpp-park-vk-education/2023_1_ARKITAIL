#include "SessionScopeMap.hpp"
#include <gtest/gtest.h>

class SessionSuit : public ::testing::Test {
protected:
	void SetUp() override {
		SessionScopeMap::instance().get();
	}

	void TearDown() override {
		SessionScopeMap::instance().remove();
	}
};

TEST_F(SessionSuit, TestCreation) {}
