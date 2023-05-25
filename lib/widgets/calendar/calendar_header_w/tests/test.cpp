#include <gtest/gtest.h>

#include <memory>

#include "calendar_header_w.hpp"

class CalendarHeaderWTest : public ::testing::Test {
  protected:
    void SetUp() override {
        header_ = std::make_unique<CalendarHeaderW>();
        header_->setSelectedDate(Wt::WDate(2003, 2, 25));
    }

    void TearDown() override {}

    std::unique_ptr<CalendarHeaderW> header_;
};

TEST_F(CalendarHeaderWTest, MonthRangeTitle) {
    header_->setValueRange(Range::MONTH);
    EXPECT_TRUE(header_->makeTitle() == Wt::WString("February 2003"));
}

TEST_F(CalendarHeaderWTest, WeekRangeTitle) {
    header_->setValueRange(Range::WEEK);
    EXPECT_EQ(header_->makeTitle().toUTF8(), "February 2003");
}

TEST_F(CalendarHeaderWTest, DayRangeTitle) {
    header_->setValueRange(Range::DAY);
    header_->setSelectedDate(Wt::WDate(2003, 2, 25));
    EXPECT_EQ(header_->makeTitle().toUTF8(), "25 February");
}

TEST_F(CalendarHeaderWTest, WeekToDayRangeTitle) {
    header_->setValueRange(Range::WEEK);
    header_->setValueRange(Range::DAY);
    EXPECT_EQ(header_->makeTitle().toUTF8(), "25 February");
}

TEST_F(CalendarHeaderWTest, MonthToDayRangeTitle) {
    header_->setValueRange(Range::MONTH);
    header_->setValueRange(Range::DAY);
    EXPECT_EQ(header_->makeTitle().toUTF8(), "25 February");
}

TEST_F(CalendarHeaderWTest, DaySwitchingBACK) {
    header_->setValueRange(Range::DAY);
    EXPECT_EQ(header_->switchSelectedDate(SwitchingDirection::BACK), Wt::WDate(2003, 2, 24));
}

TEST_F(CalendarHeaderWTest, DaySwitchingTODAY) {
    header_->setValueRange(Range::DAY);
    EXPECT_EQ(header_->switchSelectedDate(SwitchingDirection::TODAY),
              Wt::WDate(std::chrono::system_clock::now()));
}

TEST_F(CalendarHeaderWTest, DaySwitchingFORWARD) {
    header_->setValueRange(Range::DAY);
    EXPECT_EQ(header_->switchSelectedDate(SwitchingDirection::FORWARD), Wt::WDate(2003, 2, 26));
}

TEST_F(CalendarHeaderWTest, WeekSwitchingBACK) {
    header_->setValueRange(Range::WEEK);
    EXPECT_EQ(header_->switchSelectedDate(SwitchingDirection::BACK), Wt::WDate(2003, 2, 18));
}

TEST_F(CalendarHeaderWTest, WeekSwitchingTODAY) {
    header_->setValueRange(Range::WEEK);
    EXPECT_EQ(header_->switchSelectedDate(SwitchingDirection::TODAY),
              Wt::WDate(std::chrono::system_clock::now()));
}

TEST_F(CalendarHeaderWTest, WeekSwitchingFORWARD) {
    header_->setValueRange(Range::WEEK);
    EXPECT_EQ(header_->switchSelectedDate(SwitchingDirection::FORWARD), Wt::WDate(2003, 3, 4));
}
TEST_F(CalendarHeaderWTest, MonthSwitchingBACK) {
    header_->setValueRange(Range::MONTH);
    EXPECT_EQ(header_->switchSelectedDate(SwitchingDirection::BACK), Wt::WDate(2003, 1, 25));
}

TEST_F(CalendarHeaderWTest, MonthSwitchingTODAY) {
    header_->setValueRange(Range::MONTH);
    EXPECT_EQ(header_->switchSelectedDate(SwitchingDirection::TODAY),
              Wt::WDate(std::chrono::system_clock::now()));
}

TEST_F(CalendarHeaderWTest, MonthSwitchingFORWARD) {
    header_->setValueRange(Range::MONTH);
    EXPECT_EQ(header_->switchSelectedDate(SwitchingDirection::FORWARD), Wt::WDate(2003, 3, 25));
}
