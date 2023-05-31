#include <Wt/WDate.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "CalendarBodyW.hpp"
#include "CalendarW.hpp"
#include "ICalendarHeaderW.hpp"

class CalendarHeaderStub : public CalendarHeaderW {
  public:
    CalendarHeaderStub() {}
    ~CalendarHeaderStub() = default;

    void emitSelectedDateChanged() {
        change_selected_date_.emit(selected_date);
    }
    void emitRangeChanged(Range range) {
        change_range_.emit(range);
    }
    void emitEventAdded() {
        added_event_.emit();
    }
    void setSelectedDate(Wt::WDate new_date) {
        selected_date = new_date;
    }

    Wt::WDate selected_date;
};

class CalendarBodyMock : public CalendarBodyW {
  public:
    MOCK_METHOD1(updateCalendar, void(Wt::WDate*));
};

class CalendarWMock : public CalendarW {
  public:
    MOCK_METHOD1(setCalendarRange, void(Range));
};

class CalendarWTest : public ::testing::Test {
  protected:
    void SetUp() override {
        auto header_ptr = std::make_unique<CalendarHeaderStub>();
        header = header_ptr.get();
        calendar.addHeader(std::move(header_ptr));
        calendar_body_day = calendar.addCalendarBodyDay(std::make_unique<CalendarBodyMock>());
        calendar_body_week = calendar.addCalendarBodyWeek(std::make_unique<CalendarBodyMock>());
        calendar_body_month = calendar.addCalendarBodyMonth(std::make_unique<CalendarBodyMock>());
        calendar.addConnections();
    }

    void TearDown() override {}

    CalendarWMock calendar;
    CalendarHeaderStub header;
    ICalendarBodyW calendar_body_day;
    ICalendarBodyW calendar_body_week;
    ICalendarBodyW calendar_body_month;
};

TEST_F(CalendarWTest, CallUpdateRangeDayCalendar) {
    EXPECT_CALL(calendar, setCalendarRange(Range::DAY)).Times(1);
    header->emitRangeChanged(Range::DAY);
    EXPECT_TRUE(calendar_body_day->isHidden());
    EXPECT_FALSE(calendar_body_week->isHidden());
    EXPECT_FALSE(calendar_body_month->isHidden());
}

TEST_F(CalendarWTest, CallUpdateRangeWeekCalendar) {
    auto calendar = std::make_unique<CalendarWMock>();
    auto header = calendar->addHeader(std::make_unique<CalendarHeaderStub>());
    auto calendar_body_day = calendar->addCalendarBodyDay(std::make_unique<CalendarBodyMock>());
    auto calendar_body_week = calendar->addCalendarBodyWeek(std::make_unique<CalendarBodyMock>());
    auto calendar_body_month = calendar->addCalendarBodyMonth(std::make_unique<CalendarBodyMock>());
    calendar->addConnections();
    calendar->setHeaderRange();
    EXPECT_CALL(calendar, setCalendarRange(Range::WEEK)).Times(1);
    header->emitRangeChanged(Range::WEEK);
    EXPECT_FALSE(calendar_body_day->isHidden());
    EXPECT_TRUE(calendar_body_week->isHidden());
    EXPECT_FALSE(calendar_body_month->isHidden());
}

TEST_F(CalendarWTest, CallUpdateRangeMonthCalendar) {
    auto calendar = std::make_unique<CalendarWMock>();
    auto header = calendar->addHeader(std::make_unique<CalendarHeaderStub>());
    auto calendar_body_day = calendar->addCalendarBodyDay(std::make_unique<CalendarBodyMock>());
    auto calendar_body_week = calendar->addCalendarBodyWeek(std::make_unique<CalendarBodyMock>());
    auto calendar_body_month = calendar->addCalendarBodyMonth(std::make_unique<CalendarBodyMock>());
    calendar->addConnections();
    calendar->setHeaderRange();
    EXPECT_CALL(calendar, setCalendarRange(Range::MONTH)).Times(1);
    header->emitRangeChanged(Range::MONTH);
    EXPECT_FALSE(calendar_body_day->isHidden());
    EXPECT_FALSE(calendar_body_week->isHidden());
    EXPECT_TRUE(calendar_body_month->isHidden());
}

TEST_F(CalendarWTest, CallUpdateDateCalendarBodyWeek) {
    auto calendar = std::make_unique<CalendarW>();
    auto header = calendar->addHeader(std::make_unique<CalendarHeaderStub>());
    auto calendar_body_day = calendar->addCalendarBodyDay(std::make_unique<CalendarBodyMock>());
    auto calendar_body_week = calendar->addCalendarBodyWeek(std::make_unique<CalendarBodyMock>());
    auto calendar_body_month = calendar->addCalendarBodyMonth(std::make_unique<CalendarBodyMock>());
    calendar->addConnections();
    calendar->setHeaderRange();
    auto date = Wt::WDate(25, 2, 2003);
    EXPECT_CALL(*calendar_body_week, updateCalendar(date)).Times(1);
    header->setSelectedDate(date);
    header->emitSelectedDateChanged();
}
