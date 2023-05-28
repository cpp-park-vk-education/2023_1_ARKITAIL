#include "EventDbManager.hpp"

#include <memory>

#include <Wt/Dbo/Transaction.h>

#include "DbModels.hpp"

int EventDbManager::add(EventSptr event) {
  Wt::Dbo::Transaction transaction(session_);

  std::unique_ptr<db::Event> db_event_unique = std::make_unique<db::Event>();

  db_event_unique->summary = event->summary;
  db_event_unique->description = event->description;
  db_event_unique->location = event->location;
  db_event_unique->calendar =
      session_.find<db::Calendar>().where("id = ?").bind(event->calendar_id);
  db_event_unique->start = event->start;
  db_event_unique->end = event->end;
  db_event_unique->stamp = event->stamp;
  db_event_unique->frequency = event->frequency;
  db_event_unique->interval = event->interval;
  db_event_unique->until = event->until;

  db::EventPtr db_event = session_.add(std::move(db_event_unique));
  session_.flush();

  transaction.commit();
  
  id_ = db_event.id();
  return id_;
}

void EventDbManager::remove(int event_id) {
  Wt::Dbo::Transaction transaction(session_);

  db::EventPtr db_event
      = session_.find<db::Event>().where("id = ?").bind(event_id);

  if (!db_event) {
    return;
  }

  db_event.remove();

  transaction.commit();
}

void EventDbManager::update(EventSptr event) {
  Wt::Dbo::Transaction transaction(session_);

  db::EventPtr db_event
      = session_.find<db::Event>().where("id = ?").bind(event->id);

  if (!db_event) {
    return;
  }

  db_event.modify()->summary = event->summary;
  db_event.modify()->description = event->description;
  db_event.modify()->location = event->location;
  db_event.modify()->calendar
      = session_.find<db::Calendar>().where("id = ?").bind(event->calendar_id);
  db_event.modify()->start = event->start;
  db_event.modify()->end = event->end;
  db_event.modify()->stamp = event->stamp;
  db_event.modify()->frequency = event->frequency;
  db_event.modify()->interval = event->interval;
  db_event.modify()->until = event->until;

  transaction.commit();
}

EventSptr EventDbManager::get(int event_id) {
  Wt::Dbo::ptr<db::Event> db_event
      = session_.find<db::Event>().where("id = ?").bind(event_id);
  
  if (!db_event) {
    return nullptr;
  }

  Event event;
  event.id = db_event.id();
  event.summary = db_event->summary;
  event.description = db_event->description;
  event.location = db_event->location;
  event.calendar_id = db_event->calendar.id();
  event.start = db_event->start;
  event.end = db_event->end;
  event.stamp = db_event->stamp;
  event.frequency = db_event->frequency;
  event.interval = db_event->interval;
  event.until = db_event->until;

  return std::make_shared<Event>(std::move(event));
}
