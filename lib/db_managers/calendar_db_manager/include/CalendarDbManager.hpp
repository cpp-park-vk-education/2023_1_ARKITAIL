#pragma once

#include "ICalendarDbManager.hpp"
#include "mainModel.hpp"

struct RetEvent {
  int event_id;
  std::string name;
  std::string t_start;
  std::string t_end;
  std::string description;
  int calendar_id;
};


class CalendarDbManager: public ICalendarDbManager {
public:
  CalendarDbManager(dbo::Session &session) : session_(session) {}

  int Add(Calendar &);
  void Remove(int id);
  void Update(Calendar &);
  Calendar Get(int id);

  std::vector<RetEvent> GetEvents(int id);

private:
  int id_;
  dbo::Session &session_;
};