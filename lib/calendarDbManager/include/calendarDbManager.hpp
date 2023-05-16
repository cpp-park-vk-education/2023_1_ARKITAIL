#pragma once

#include "mainModel.hpp"

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
  int add(Ret_Calen&);
  void remove(const int id);
  void update(Ret_Calen&);
  Ret_Calen get(const int id);

  std::vector<Ret_Event> getEvents(const int id);

private:
  int id;
  dbo::Session &session_;
};