#include <gtest/gtest.h>

#include <memory>

#include "calendar_header_w.hpp"

class CalendarHeaderWTest : public ::testing::Test {
  protected:
    void SetUp() override {
        header_.setSelectedDate(Wt::WDate(25, 2, 2003));
    }

    void TearDown() override {}

    CalendarHeaderW header_;
};

TEST_F(CalendarHeaderWTest, MonthRangeTitle) {
    header_.setOptionsRange(0);
    ASSERT_EQ(header_.makeTitle().toUTF8(), "February 2003");
}

TEST_F(CalendarHeaderWTest, WeekRangeTitle) {
    header_.setOptionsRange(1);
    ASSERT_EQ(header_.makeTitle().toUTF8(), "February 2003");
}

TEST_F(CalendarHeaderWTest, DayRangeTitle) {
    header_.setOptionsRange(2);
    header_.setSelectedDate(Wt::WDate(25, 2, 2003));
    ASSERT_EQ(header_.makeTitle().toUTF8(), "25 February");
}

TEST_F(CalendarHeaderWTest, WeekToDayRangeTitle) {
    header_.setOptionsRange(2);
    ASSERT_EQ(header_.makeTitle().toUTF8(), "25 February");
}

TEST_F(CalendarHeaderWTest, MonthToDayRangeTitle) {
    header_.setOptionsRange(0);
    header_.setOptionsRange(2);
    ASSERT_EQ(header_.makeTitle().toUTF8(), "25 February");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return 0;
}
