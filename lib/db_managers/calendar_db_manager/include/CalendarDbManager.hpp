#pragma once

#include "mainModel.hpp"
#include "ICalendarDbManager.hpp"
class CalendarDbManager: public ICalendarDbManager {
public:
  CalendarDbManager(dbo::Session &session) : session_(session) {}

  int add(const Calendar &);
  void remove(int calendar_id);
  void update(const Calendar &);
  const Calendar& get(int calendar_id);

  std::vector<Event> getEvents(int calendar_id);

private:
  int id_;
  dbo::Session &session_;
};