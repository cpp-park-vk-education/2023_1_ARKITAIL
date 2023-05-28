#pragma once

#include <Wt/Dbo/Session.h>

#include "DbModels.hpp"
#include "ICalendarDbManager.hpp"

class CalendarDbManager: public ICalendarDbManager {
public:
  CalendarDbManager(Wt::Dbo::Session& session) : session_(session) {}

  int add(CalendarSptr) override;
  void remove(int calendar_id) override;
  void update(CalendarSptr) override;
  CalendarSptr get(int calendar_id) override;

  std::vector<Event> getEvents(int calendar_id) override;

private:
  int id_;
  Wt::Dbo::Session &session_;
};
