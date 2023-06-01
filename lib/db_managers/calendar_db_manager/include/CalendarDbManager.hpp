#pragma once

#include "DbModels.hpp"
#include "ICalendarDbManager.hpp"
#include "Session.hpp"

class CalendarDbManager: public ICalendarDbManager {
public:
  CalendarDbManager() = delete;
  explicit CalendarDbManager(Session& session);

  int add(CalendarSptr calendar) override;
  void remove(int calendar_id) override;
  void update(CalendarSptr calendar) override;
  CalendarSptr get(int calendar_id) override;

  std::vector<Event> getEvents(int calendar_id) override;

private:
  Session& session_;

};

