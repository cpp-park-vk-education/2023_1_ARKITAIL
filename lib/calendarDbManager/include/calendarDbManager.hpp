#pragma once

#include "mainModel.hpp"

struct RetEvent {
  int event_id;
  std::string name;
  std::string t_start;
  std::string t_end;
  std::string description;
  int calendar_id;
};

struct RetCalen {
  int calendar_id;
  int user_id;
  std::string name;
  std::string description;
};

class CalendarManager {
public:
  CalendarManager(dbo::Session &session) : session_(session) {}

  int Add(RetCalen &);
  void Remove(int id);
  void Update(RetCalen &);
  RetCalen Get(int id);

  std::vector<RetEvent> GetEvents(int id);

private:
  int id_;
  dbo::Session &session_;
};