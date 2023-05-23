#pragma once

#include "mainModel.hpp"
#include "IEventDbManager.hpp"

class EventDbManager: IEventDbManager {
public:
  EventDbManager(dbo::Session &session) : session_(session) {}

  int add(const Event &);
  void remove(int event_id);
  void update(const Event &);
  const Event& get(int event_id);

  //std::vector<Comment> getComments(int event_id)

private:
  int id_;
  dbo::Session &session_;
};