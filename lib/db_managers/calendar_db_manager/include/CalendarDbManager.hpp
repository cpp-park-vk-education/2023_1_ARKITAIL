#pragma once

#include "ICalendarDbManager.hpp"
#include "mainModel.hpp"


class CalendarDbManager: public ICalendarDbManager {
public:
  CalendarDbManager(dbo::Session &session) : session_(session) {}

  int add(const Calendar &);
  void remove(int);
  void update(const Calendar &);
  const Calendar& get(int);

  std::vector<Event> getEvents(int);

private:
  int id_;
  dbo::Session &session_;
};