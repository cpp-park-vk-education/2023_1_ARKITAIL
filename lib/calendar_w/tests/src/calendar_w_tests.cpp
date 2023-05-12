#include <Wt/WDate.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "calendar_body_w.hpp"
#include "calendar_header_w.hpp"
#include "calendar_w.hpp"
#include "utils.hpp"

class CalendarHeaderMock : public InterfaceCalendarHeaderW {
    CalendarHeaderMock();
    ~CalendarHeaderMock() = default;

    Wt::Signal<Wt::WDate>& selectedDateChanged() override { return change_selected_date_; }
    Wt::Signal<Range>& rangeChanged() override { return change_range_; }
    Wt::Signal<>& eventAdded() override { return added_event_; }
    void setRange() override {}
    Wt::WString makeTitle() override {}
    void addStyle() override {}
    void switchToToday() override {}
    void switchToPrev() override {}
    void switchToNext() override {}
    void emitSelectedDateChanged() { change_selected_date_.emit(selected_date_); }
    void emitRangeChanged(Range range) { change_range_.emit(range); }
    void emitEventAdded() { added_event_.emit(); }
    void setSelectedDate(std::unique_ptr<Wt::WDate> new_date) { selected_date_ = std::move(new_date); }

    Wt::Signal<Wt::WDate> change_selected_date_;
    Wt::Signal<Range> change_range_;
    Wt::Signal<> added_event_;
    std::unique_ptr<Wt::WDate> selected_date_;
}

class CalendarBodyMock : public InterfaceCalendarBodyW {
    CalendarBodyMock();
    ~CalendarBodyMock() = default;
    MOCK_METHOD(void, updateCalendar, (Wt::WDate*), (override));
}

TEST(CalendarWTest, CallUpdateDateCalendar) {
    auto calendar = std::make_unique<CalendarW>();
    auto header = calendar->addHeader(std::make_unique<CalendarHeaderMock>());
    auto calendar_body_day = calendar->addBodyCalendarDay(std::make_unique<CalendarBodyMock>());
    auto calendar_body_week = calendar->addBodyCalendarWeek(std::make_unique<CalendarBodyMock>());
    auto calendar_body_month = calendar->addBodyCalendarMonth(std::make_unique<CalendarBodyMock>());
    calendar->addConnections();
    calendar->setHeaderRange();
    auto date = std::make_unique<Wt::WDate>(25, 2, 2003);
    EXPECT_CALL(calendar_body, updateCalendar(date.get())).Times(1);
    header->setSelectedDate(std::move(date));
    header->emitSelectedDateChanged();
}

TEST(CalendarWTest, CallUpdateRangeDayCalendar) {
    auto calendar = std::make_unique<CalendarW>();
    auto header = calendar->addHeader(std::make_unique<CalendarHeaderMock>());
    auto calendar_body_day = calendar->addBodyCalendarDay(std::make_unique<CalendarBodyMock>());
    auto calendar_body_week = calendar->addBodyCalendarWeek(std::make_unique<CalendarBodyMock>());
    auto calendar_body_month = calendar->addBodyCalendarMonth(std::make_unique<CalendarBodyMock>());
    calendar->addConnections();
    calendar->setHeaderRange();
    EXPECT_CALL(calendar, setCalendarRange(DAY)).Times(1);
    header->emitRangeChanged(DAY);
    EXPECT_TRUE(calendar_body_day->isHidden());
    EXPECT_FALSE(calendar_body_week->isHidden());
    EXPECT_FALSE(calendar_body_month->isHidden());
}

TEST(CalendarWTest, CallUpdateRangeWeekCalendar) {
    auto calendar = std::make_unique<CalendarW>();
    auto header = calendar->addHeader(std::make_unique<CalendarHeaderMock>());
    auto calendar_body_day = calendar->addBodyCalendarDay(std::make_unique<CalendarBodyMock>());
    auto calendar_body_week = calendar->addBodyCalendarWeek(std::make_unique<CalendarBodyMock>());
    auto calendar_body_month = calendar->addBodyCalendarMonth(std::make_unique<CalendarBodyMock>());
    calendar->addConnections();
    calendar->setHeaderRange();
    EXPECT_CALL(calendar, setCalendarRange(WEEK)).Times(1);
    header->emitRangeChanged(WEEK);
    EXPECT_FALSE(calendar_body_day->isHidden());
    EXPECT_TRUE(calendar_body_week->isHidden());
    EXPECT_FALSE(calendar_body_month->isHidden());
}

TEST(CalendarWTest, CallUpdateRangeMonthCalendar) {
    auto calendar = std::make_unique<CalendarW>();
    auto header = calendar->addHeader(std::make_unique<CalendarHeaderMock>());
    auto calendar_body_day = calendar->addBodyCalendarDay(std::make_unique<CalendarBodyMock>());
    auto calendar_body_week = calendar->addBodyCalendarWeek(std::make_unique<CalendarBodyMock>());
    auto calendar_body_month = calendar->addBodyCalendarMonth(std::make_unique<CalendarBodyMock>());
    calendar->addConnections();
    calendar->setHeaderRange();
    EXPECT_CALL(calendar, setCalendarRange(MONTH)).Times(1);
    header->emitRangeChanged(MONTH);
    EXPECT_FALSE(calendar_body_day->isHidden());
    EXPECT_FALSE(calendar_body_week->isHidden());
    EXPECT_TRUE(calendar_body_month->isHidden());
}
