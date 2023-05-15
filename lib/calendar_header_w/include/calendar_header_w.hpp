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

class CalendarHeaderW : public InterfaceCalendarHeaderW {
  public:
    CalendarHeaderW();
    ~CalendarHeaderW() = default;

    Wt::Signal<Wt::WDate>& selectedDateChanged() override { return change_selected_date_; }
    Wt::Signal<Range>& rangeChanged() override { return change_range_; }
    Wt::Signal<>& eventAdded() override { return added_event_; }
    void setRange() override;
    Wt::WString makeTitle() override;
    void setSelectedDate(std::unique_ptr<Wt::WDate> new_date) { selected_date_ = std::move(new_date); }

  protected:
    Range range_;
    std::unique_ptr<Wt::WDate> selected_date_;
    Wt::WPushButton* today_button_;
    Wt::WPushButton* prev_button_;
    Wt::WPushButton* next_button_;
    Wt::WText* calendar_title_;
    Wt::WContainerWidget* container_option_range_;
    Wt::Signal<> added_event_;
    Wt::Signal<Wt::WDate> change_selected_date_;
    Wt::WComboBox* option_range_;

    virtual void addConnections() override;

  private:
    Wt::Signal<Range> change_range_;

    void addStyle() override;
    void switchToToday() override;
    void switchToPrev() override;
    void switchToNext() override;
};
