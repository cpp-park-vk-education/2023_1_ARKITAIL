#include <gtest/gtest.h>

#include <memory>

#include "calendar_header_w.hpp"

TEST(CalendarHeaderWTest, MonthRangeTitle) {
    auto header = std::make_unique<CalendarHeaderW>();
    header->option_range_->setCurrentIndex(0);
    header->setSelectedDate(std::make_unique<Wt::WDate>(25, 2, 2003));
    EXPECT_EQ(header->makeTitle(), Wt::WString("February 2003"));
}

TEST(CalendarHeaderWTest, WeekRangeTitle) {
    auto header = std::make_unique<CalendarHeaderW>();
    header->option_range_->setCurrentIndex(1);
    header->setSelectedDate(std::make_unique<Wt::WDate>(25, 2, 2003));
    EXPECT_EQ(header->makeTitle(), Wt::WString("February 2003"));
}

TEST(CalendarHeaderWTest, MonthRangeTitle) {
    auto header = std::make_unique<CalendarHeaderW>();
    header->option_range_->setCurrentIndex(2);
    header->setSelectedDate(std::make_unique<Wt::WDate>(25, 2, 2003));
    EXPECT_EQ(header->makeTitle(), Wt::WString("25 February"));
}
