#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

#include <Directory.hpp>
#include <vector>

#include "Calendar.hpp"
#include "CalendarCardW.hpp"

class CalendarCardContainerW : public Wt::WContainerWidget {
  public:
    CalendarCardContainerW();
    void init(const std::vector<CalendarSptr>& content);

  private:
    Wt::WText* status_;
    std::vector<CalendarCardW*> calendar_cards_;
};
