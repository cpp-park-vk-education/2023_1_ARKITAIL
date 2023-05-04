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

#include "AddEventDialog.hpp"
#include "CalendarHeaderW.hpp"

class PersonalCalendarHeaderW : public CalendarHeaderW {
  public:
    PersonalCalendarHeaderW();
    ~PersonalCalendarHeaderW() = default;

  private:
    Wt::WPushButton* button_add_event_;
    AddEventDialog* add_event_dialog_;

    void addConnections() override;
};
