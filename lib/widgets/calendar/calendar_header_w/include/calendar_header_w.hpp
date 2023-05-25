#pragma once

#include <Wt/WComboBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDate.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>
#include <Wt/WText.h>
#include <Wt/WTime.h>

#include <memory>

#include "i_calendar_header_w.hpp"

enum SwitchingDirection {
    BACK = -1,
    TODAY,
    FORWARD
};

class CalendarHeaderW : public ICalendarHeaderW {
  public:
    CalendarHeaderW();
    ~CalendarHeaderW() = default;

    Wt::Signal<Wt::WDate>& selectedDateChanged() override;
    Wt::Signal<Range>& rangeChanged() override;
    Wt::Signal<>& eventAdded() override;

    void setRange() override;
    Wt::WString makeTitle() override;

    void setSelectedDate(Wt::WDate new_date);
    void setValueRange(Range range);

    CalendarHeaderW* addConnections() override;
    CalendarHeaderW* addButtons() override;

    Wt::WDate switchSelectedDate(SwitchingDirection direction);

  protected:
    Range range_;
    Wt::WDate selected_date_;
    Wt::WPushButton* today_button_;
    Wt::WPushButton* prev_button_;
    Wt::WPushButton* next_button_;
    Wt::WContainerWidget* container_option_range_;
    Wt::WText* calendar_title_;
    Wt::Signal<> added_event_;
    Wt::Signal<Wt::WDate> change_selected_date_;
    Wt::Signal<Range> change_range_;
    Wt::WComboBox* option_range_;

  private:
    void addStyle() override;

    void switchToToday() override;
    void switchToPrev() override;
    void switchToNext() override;
};
