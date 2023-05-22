#include "CalendarDbManager.hpp"

int CalendarDbManager::add(const Calendar &ret) {
  dbo::Transaction transaction(session_);

  std::unique_ptr<Calendars> calendar{new Calendars()};
  calendar->name = ret.name;
  calendar->description = ret.description;
  calendar->user = session_.find<Users>().where("id = ?").bind(ret.owner_id);

  dbo::ptr<Calendars> calendarPtr = session_.add(std::move(calendar));
  session_.flush();
  transaction.commit();
  id_ = calendarPtr.id();

  return id_;
}

void CalendarDbManager::remove(int) {
  dbo::Transaction transaction(session_);
  int id;
  dbo::ptr<Calendars> calendar =
      session_.find<Calendars>().where("id = ?").bind(id);
  if (!calendar) {
    return;
  }
  calendar.remove();
  transaction.commit();
}

void CalendarDbManager::update(const Calendar &ret) {
  dbo::Transaction transaction(session_);

  dbo::ptr<Calendars> calendar =
      session_.find<Calendars>().where("name = ?").bind(ret.name);
  if (!calendar) {
    return;
  }
  calendar.modify()->name = ret.name;
  calendar.modify()->description = ret.description;
  calendar.modify()->user =
      session_.find<Users>().where("id = ?").bind(ret.owner_id);

  transaction.commit();
}
const Calendar &CalendarDbManager::get(int) {
  dbo::Transaction transaction(session_);
  int id;
  Calendar ret;
  dbo::ptr<Calendars> calendar =
      session_.find<Calendars>().where("id = ?").bind(id);
  if (!calendar) {
    ret.name = "error";
    return ret;
  }
  ret.name = calendar->name;
  ret.description = calendar->description;
  ret.owner_id = calendar->user.id();

  transaction.commit();

  return ret;
}

std::vector<Event> CalendarDbManager::getEvents(int) {
  int id;
  Event ret;
  std::vector<Event> v;

  dbo::Transaction transaction(session_);
  dbo::ptr<Calendars> calendar =
      session_.find<Calendars>().where("id = ?").bind(id);
  dbo::collection<dbo::ptr<Events>> event =
      session_.find<Events>().where("calendar_id = ?").bind(id);
  if (!calendar) {
    ret.name = "error";
    v.push_back(ret);
    return v;
  }
  for (const dbo::ptr<Events> &eve : event) {

    ret.name = eve->name;
    ret.description = eve->description;
    ret.calendar_id = eve->calendar.id();
    ret.begin_point = eve->time_start.toString().toUTF8();
    ret.end_point = eve->time_end.toString().toUTF8();

    v.push_back(ret);
  }

  transaction.commit();

  return v;
}
