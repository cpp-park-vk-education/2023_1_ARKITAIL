#pragma once

#include "mainModel.hpp"

struct Ret_Event {
  int event_id;
  std::string name;
  std::string t_start;
  std::string t_end;
  std::string description;
  int calendar_id;
};

struct Ret_Calen {
  int calendar_id;
  int user_id;
  std::string name;
  std::string description;
  int node_id;
};

class CalendarManager {
public:
  CalendarManager(dbo::Session &session) : session_(session) {}

  int add(Ret_Calen &);
  void remove(const int id);
  void update(Ret_Calen &);
  Ret_Calen get(const int id);

  std::vector<Ret_Event> getEvents(const int id);

private:
  int id;
  dbo::Session &session_;
};