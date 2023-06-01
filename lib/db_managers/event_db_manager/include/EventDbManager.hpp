#pragma once

#include "DbModels.hpp"
#include "IEventDbManager.hpp"
#include "Session.hpp"

class EventDbManager: public IEventDbManager {
public:
  explicit EventDbManager(Session& session);

  int add(EventSptr event) override;
  void remove(int event_id) override;
  void update(EventSptr event) override;
  EventSptr get(int event_id) override;

private:
  Session& session_;

};

