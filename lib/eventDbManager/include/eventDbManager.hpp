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

class EventManager {
public:
  EventManager(dbo::Session &session) : session_(session) {}

  int Add(RetEvent &);
  void Remove(int id);
  void Update(RetEvent &);
  RetEvent Get(int id);

private:
  int id_;
  dbo::Session &session_;
};