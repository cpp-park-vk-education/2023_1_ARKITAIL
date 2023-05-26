#include "CalendarDbManager.hpp"
#include "Calendar.hpp"
#include "DbModels.hpp"

#include <Wt/Dbo/Transaction.h>
#include <Wt/Dbo/collection.h>

int CalendarDbManager::add(CalendarSptr calendar) {
  Wt::Dbo::Transaction transaction(session_);

  std::unique_ptr<db::Calendar> db_calendar_unique = std::make_unique<db::Calendar>();
  db_calendar_unique->summary = calendar->summary;
  db_calendar_unique->description = calendar->description;
  db_calendar_unique->user
      = session_.find<db::User>().where("id = ?").bind(calendar->owner_id);

  db::CalendarPtr db_calendar = session_.add(std::move(db_calendar_unique));
  session_.flush();
  
  // нужна ли здесь транзация?..
  transaction.commit();

  return db_calendar.id();
}

void CalendarDbManager::remove(int calendar_id) {
  Wt::Dbo::Transaction transaction(session_);

  db::CalendarPtr db_calendar
      = session_.find<db::Calendar>().where("id = ?").bind(calendar_id);

  if (!db_calendar) {
    return;
  }

  db_calendar.remove();

  transaction.commit();
}

void CalendarDbManager::update(CalendarSptr calendar) {
  Wt::Dbo::Transaction transaction(session_);

  db::CalendarPtr db_calendar =
      session_.find<db::Calendar>().where("name = ?").bind(calendar->summary);

  if (!db_calendar) {
    return;
  }
  db_calendar.modify()->description = calendar->description;
  db_calendar.modify()->user =
      session_.find<db::User>().where("id = ?").bind(calendar->owner_id);

  transaction.commit();
}

CalendarSptr CalendarDbManager::get(int calendar_id) {
  db::CalendarPtr db_calendar
      = session_.find<db::Calendar>().where("id = ?").bind(calendar_id);

  if (!db_calendar) {
    return nullptr;
  }

  Calendar calendar;
  calendar.id = db_calendar.id();
  calendar.owner_id = db_calendar->user.id();
  calendar.node_id = db_calendar->node.id();
  calendar.summary = db_calendar->summary;
  calendar.description = db_calendar->description;
  calendar.summary = db_calendar->summary;
  
  return std::make_shared<Calendar>(std::move(calendar));
}

std::vector<Event> CalendarDbManager::getEvents(int calendar_id) {
  db::CalendarPtr db_calendar =
      session_.find<db::Calendar>().where("id = ?").bind(calendar_id);

  Wt::Dbo::collection<db::EventPtr> db_events =
      session_.find<db::Event>().where("calendar_id = ?").bind(calendar_id);

  if (!db_calendar) {
    return std::vector<Event>();
  }

  std::vector<Event> events;
  for (const db::EventPtr& db_event : db_events) {
    Event event;
    event.id = db_event.id();
    event.calendar_id = db_calendar.id();
    event.summary = db_event->summary;
    event.description = db_event->description;
    event.start = db_event->start;
    event.end = db_event->end;
    // ...

    events.push_back(std::move(event));
  }

  return events;
}
