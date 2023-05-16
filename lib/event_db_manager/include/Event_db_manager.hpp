#pragma once

#include "Main_model.hpp"

struct Ret_Event {
  std::string name;
  std::array<int, 6> t_start;
  std::array<int, 6> t_end;
  std::string description;
  int calendar_id;
};

class event_manager {
public:
  event_manager(dbo::Session &session) : session_(session) {}

  int addEvent(Ret_Event &);
  void removeEvent(const int id);
  void upgradeEvent(Ret_Event &);
  Ret_Event getEvent(const int id);

private:
  int id;
  dbo::Session &session_;
};