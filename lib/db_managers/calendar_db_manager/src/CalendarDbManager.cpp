#include "CalendarDbManager.hpp"

#include <vector>

#include <Wt/WColor.h>
#include <Wt/Dbo/Transaction.h>
#include <Wt/Dbo/collection.h>

#include "Calendar.hpp"
#include "DbModels.hpp"
#include "Event.hpp"
#include "Session.hpp"

CalendarDbManager::CalendarDbManager(Session& session)
    : session_(session) {
}

int CalendarDbManager::add(CalendarSptr calendar) {
  Wt::Dbo::Transaction transaction(session_);

  // запрашиваем всё необходимое для создания календаря
  db::UserPtr db_user
      = session_.find<db::User>().where("id = ?").bind(calendar->owner_id);
  
  if (!db_user) {
    Wt::log("CalendarDbManager::add: not found calendar's user with id = "
        + std::to_string(calendar->owner_id));
    return -1;
  }

  db::NodePtr db_node
    = session_.find<db::Node>().where("id = ?").bind(calendar->node_id);
  
  if (!db_node) {
    Wt::log("CalendarDbManager::add: not found calendar's node with id = "
        + std::to_string(calendar->node_id));
    return -1;
  }

  // создаём календарь
  db::CalendarPtr db_calendar = session_.add(std::make_unique<db::Calendar>());

  // непосредственно сохраняем, чтобы получить id
  session_.flush();
  int id = db_calendar.id();

  // устанавливаем поля
  db_calendar.modify()->user = db_user;
  db_calendar.modify()->node = db_node;
  
  db_calendar.modify()->summary = calendar->summary;
  db_calendar.modify()->description = calendar->description;
  db_calendar.modify()->visibility = calendar->visibility;
  db_calendar.modify()->color = calendar->color.cssText();
  
  transaction.commit();

  return id;
}

void CalendarDbManager::remove(int calendar_id) {
  Wt::Dbo::Transaction transaction(session_);

  db::CalendarPtr db_calendar
      = session_.find<db::Calendar>().where("id = ?").bind(calendar_id);

  if (!db_calendar) {
    Wt::log("CalendarDbManager::remove: not found calendar with id = "
        + std::to_string(calendar_id));
    return;
  }

  db_calendar.remove();

  transaction.commit();
}

void CalendarDbManager::update(CalendarSptr calendar) {
  Wt::Dbo::Transaction transaction(session_);

  db::CalendarPtr db_calendar
      = session_.find<db::Calendar>().where("id = ?").bind(calendar->id);

  if (!db_calendar) {
    Wt::log("CalendarDbManager::update: not found calendar with id = "
        + std::to_string(calendar->id));
    return;
  }
  
  db::UserPtr db_new_user
      = session_.find<db::User>().where("id = ?").bind(calendar->owner_id);

  if (!db_new_user) {
    Wt::log("CalendarDbManager::update: not found calendar's new user with id = "
        + std::to_string(calendar->owner_id));
    return;
  }

  db::NodePtr db_new_node
      = session_.find<db::Node>().where("id = ?").bind(calendar->node_id);

  if (!db_new_node) {
    Wt::log("CalendarDbManager::update: not found calendar's new node with id = "
        + std::to_string(calendar->node_id));
    return;
  }

  db_calendar.modify()->user = db_new_user;
  db_calendar.modify()->node = db_new_node;
  
  db_calendar.modify()->summary = calendar->summary;
  db_calendar.modify()->description = calendar->description;
  db_calendar.modify()->visibility = calendar->visibility;
  db_calendar.modify()->color = calendar->color.cssText();

  transaction.commit();
}

CalendarSptr CalendarDbManager::get(int calendar_id) {
  Wt::Dbo::Transaction transaction(session_);

  db::CalendarPtr db_calendar
      = session_.find<db::Calendar>().where("id = ?").bind(calendar_id);

  if (!db_calendar) {
    Wt::log("CalendarDbManager::get: not found calendar with id = "
        + std::to_string(calendar_id));
    return std::make_shared<Calendar>();
  }

  Calendar calendar {
    static_cast<int>(db_calendar.id()),
    static_cast<int>(db_calendar->node.id()),
    static_cast<int>(db_calendar->user.id()),
    db_calendar->summary,
    db_calendar->description,
    db_calendar->visibility,
    Wt::WColor(db_calendar->color),
  };

  transaction.commit();
  
  return std::make_shared<Calendar>(std::move(calendar));
}

std::vector<Event> CalendarDbManager::getEvents(int calendar_id) {
  Wt::Dbo::Transaction transaction(session_);
  
  Wt::Dbo::collection<db::EventPtr> db_events =
      session_.find<db::Event>().where("calendar_id = ?").bind(calendar_id);

  if (db_events.empty()) {
    Wt::log("CalendarDbManager::getEvents: not found events for calendar with id = "
        + std::to_string(calendar_id));
    return std::vector<Event>();
  }

  std::vector<Event> events;
  for (const db::EventPtr& db_event : db_events) {
    events.push_back(Event {
        static_cast<int>(db_event.id()),
        static_cast<int>(db_event->calendar.id()), // совпадает с calendar_id
        
        db_event->summary,
        db_event->description,
        db_event->location,
        
        db_event->start,
        db_event->end,
        db_event->stamp,

        db_event->frequency,
        db_event->interval,
        db_event->until,
    });
  }

  transaction.commit();

  return events;
}

