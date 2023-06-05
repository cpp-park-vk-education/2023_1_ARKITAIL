#include "EventDbManager.hpp"

#include <memory>
#include <string>

#include <Wt/WLogger.h>
#include <Wt/Dbo/Transaction.h>

#include "DbModels.hpp"
#include "Event.hpp"
#include "Session.hpp"

EventDbManager::EventDbManager(Session& session)
    : session_(session) {
}

int EventDbManager::add(EventSptr event) {
  Wt::Dbo::Transaction transaction(session_);

  // достаём всё необходимое для создания события
  db::CalendarPtr db_calendar
      = session_.find<db::Calendar>().where("id = ?").bind(event->calendar_id);

  if (!db_calendar) {
    Wt::log("EventDbManager::add: not found event's calendar with id = "
        + std::to_string(event->calendar_id));
    return -1;
  }

  // создаём событие
  db::EventPtr db_event
      = session_.add(std::make_unique<db::Event>());

  // непосредственно сохраняем, чтобы получить id
  session_.flush();
  int id = static_cast<int>(db_event.id());

  // устанавливаем поля
  db_event.modify()->calendar = db_calendar;

  db_event.modify()->summary = event->summary;
  db_event.modify()->description = event->description;
  db_event.modify()->location = event->location;

  db_event.modify()->start = event->start;
  db_event.modify()->end = event->end;
  db_event.modify()->stamp = event->stamp;

  db_event.modify()->frequency = event->frequency;
  db_event.modify()->interval = event->interval;
  db_event.modify()->until = event->until;
  
  transaction.commit();
  
  return id;
}

void EventDbManager::remove(int event_id) {
  Wt::Dbo::Transaction transaction(session_);

  db::EventPtr db_event
      = session_.find<db::Event>().where("id = ?").bind(event_id);

  if (!db_event) {
    Wt::log("EventDbManager::remove: not found event with id = "
        + std::to_string(event_id));
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
    Wt::log("EventDbManager::update: not found event with id = "
        + std::to_string(event->id));
    return;
  }

  db::CalendarPtr db_calendar
      = session_.find<db::Calendar>().where("id = ?").bind(event->calendar_id);

  if (!db_calendar) {
    Wt::log("EventDbManager::update: not found event's calendar with id = "
        + std::to_string(event->calendar_id));
    return;
  }

  db_event.modify()->summary = event->summary;
  db_event.modify()->description = event->description;
  db_event.modify()->location = event->location;

  db_event.modify()->calendar = db_calendar;

  db_event.modify()->start = event->start;
  db_event.modify()->end = event->end;
  db_event.modify()->stamp = event->stamp;

  db_event.modify()->frequency = event->frequency;
  db_event.modify()->interval = event->interval;
  db_event.modify()->until = event->until;

  transaction.commit();
}

EventSptr EventDbManager::get(int event_id) {
  Wt::Dbo::Transaction transaction(session_);

  Wt::Dbo::ptr<db::Event> db_event
      = session_.find<db::Event>().where("id = ?").bind(event_id);
  
  if (!db_event) {
    Wt::log("EventDbManager::get: not found event with id = "
        + std::to_string(event_id));
    return std::make_shared<Event>();
  }

  Event event {
    static_cast<int>(db_event.id()),
    static_cast<int>(db_event->calendar.id()),
    
    db_event->summary,
    db_event->description,
    db_event->location,
    
    db_event->start,
    db_event->end,
    db_event->stamp,

    db_event->frequency,
    db_event->interval,
    db_event->until,
  };

  transaction.commit();

  return std::make_shared<Event>(std::move(event));
}

