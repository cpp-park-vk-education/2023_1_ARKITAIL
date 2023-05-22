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

class EventManager {
public:
  EventManager(dbo::Session &session) : session_(session) {}

  int add(Ret_Event &);
  void remove(const int id);
  void update(Ret_Event &);
  Ret_Event get(const int id);

private:
  int id;
  dbo::Session &session_;
};