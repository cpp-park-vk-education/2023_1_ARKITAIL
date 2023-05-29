#pragma once

#include "DbModels.hpp"
#include "IEventDbManager.hpp"

class EventDbManager: public IEventDbManager {
public:
  explicit EventDbManager(Wt::Dbo::Session &session) : session_(session) {}

  int add(EventSptr) override;
  void remove(int event_id) override;
  void update(EventSptr) override;
  EventSptr get(int event_id) override;

  //std::vector<Comment> getComments(int event_id)

private:
  int id_;
  Wt::Dbo::Session &session_;
};
