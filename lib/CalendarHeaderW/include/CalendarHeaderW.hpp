#pragma once
#include <Wt/WComboBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDate.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>
#include <Wt/WText.h>
#include <Wt/WTime.h>

#include <memory>

#include "utils.hpp"

class CalendarHeaderW : public Wt::WContainerWidget {
  public:
    CalendarHeaderW();
    ~CalendarHeaderW() = default;

    Wt::Signal<Wt::WDate>& selectedDateChanged() { return change_selected_date_; }
    Wt::Signal<Range>& rangeChanged() { return change_range_; }
    Wt::Signal<>& eventAdded() { return added_event_; }
    void setRange();

  protected:
    Range range_;
    std::unique_ptr<Wt::WDate> selected_date_;
    Wt::WPushButton* today_button_;
    Wt::WPushButton* prev_button_;
    Wt::WPushButton* next_button_;
    Wt::WText* calendar_title_;
    Wt::WComboBox* option_range_;
    Wt::WContainerWidget* container_option_range_;
    Wt::Signal<> added_event_;

    virtual void addConnections();

  private:
    Wt::Signal<Wt::WDate> change_selected_date_;
    Wt::Signal<Range> change_range_;

    Wt::WString makeTitle();
    void addStyle();
    void switchToToday();
    void switchToPrev();
    void switchToNext();
};
