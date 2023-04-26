#pragma once

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WCheckBox.h>
#include <Wt/WComboBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDate.h>
#include <Wt/WDateEdit.h>
#include <Wt/WDateValidator.h>
#include <Wt/WDialog.h>
#include <Wt/WEnvironment.h>
#include <Wt/WLabel.h>
#include <Wt/WLengthValidator.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>
#include <Wt/WTextArea.h>
#include <Wt/WTime.h>
#include <Wt/WTimeEdit.h>
#include <Wt/WTimeValidator.h>
#include <Wt/WValidator.h>

#include "event.hpp"

enum Range { day = 2, week = 1, month = 0 };

class Calendar : public Wt::WContainerWidget {
  public:
    Calendar();
    ~Calendar() = default;
    void updateCalendar();

  private:
    Range range;
    std::unique_ptr<Wt::WDate> selected_date;
    Wt::WTable *table_;
    Wt::WPushButton *today_button;
    Wt::WPushButton *prev_day_button;
    Wt::WPushButton *next_day_button;
    Wt::WText *calendar_title;
    Wt::WComboBox *option_range;
    Wt::WPushButton *button_add_event;

    Wt::WString makeTitle();
    void setRange(Range new_range);
    void today();
    void prevDay();
    void nextDay();
    void addEvent();
    void showAddEventModal(Wt::WObject *owner);
    void addNavbar();
    void makeHeaderWeek();
    void makeHeaderTime();
    void addStyles();
    void addSignals();
    void activateToday(int beginWeekDay);
    void activateToday();
};
