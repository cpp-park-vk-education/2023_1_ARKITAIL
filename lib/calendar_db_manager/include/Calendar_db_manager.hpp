#pragma once

#include "Main_model.hpp"

struct Ret_Event {
  std::string name;
  std::array<int, 6> t_start;
  std::array<int, 6> t_end;
  std::string description;
  int calendar_id;
};

struct Ret_Calen {
  int user_id;
  std::string name;
  std::string description;
  int node_id;
};

class calendars_manager {
public:
  int addCalendar(Ret_Calen&);
  void removeCalendar(const int id);
  void updateCalendar(Ret_Calen&);
  Ret_Calen getCalendar(const int id);

  std::vector<Ret_Event> getEvent(const int id);

private:
  int id;
  dbo::Session &session_;
};