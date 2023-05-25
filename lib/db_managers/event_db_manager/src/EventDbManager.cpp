#include "EventDbManager.hpp"

// time_start и time_end передаются в виде "0, 0, 0, 14, 4, 2023 - 1900",
// где это сек, мин, час, д, мес, год
int EventDbManager::add(const Event &ret) {

  
  dbo::Transaction transaction(session_);

  std::unique_ptr<Events> event{new Events()};
  event->name = ret.name;
  event->description = ret.description;
  event->calendar =
      session_.find<Calendars>().where("id = ?").bind(ret.calendar_id);
  Wt::WString time_help =  Wt::WString::fromUTF8(ret.begin_point);
  event->time_start = Wt::WDateTime::fromString(time_help);
  std::cout << time_help << std::endl;
  time_help =  Wt::WString::fromUTF8(ret.end_point);
  event->time_end = Wt::WDateTime::fromString(ret.end_point);

  dbo::ptr<Events> eventPtr = session_.add(std::move(event));
  session_.flush();
  transaction.commit();
  id_ = eventPtr.id();
  return id_;
}

void EventDbManager::remove(int event_id) {
  dbo::Transaction transaction(session_);

  dbo::ptr<Events> event = session_.find<Events>().where("id = ?").bind(event_id);
  if (!event) {
    return;
  }
  event.remove();
  transaction.commit();
}

void EventDbManager::update(const Event &ret) {
  dbo::Transaction transaction(session_);

  dbo::ptr<Events> event =
      session_.find<Events>().where("id = ?").bind(ret.id);
  if (!event) {
    return;
  }
  event.modify()->name = ret.name;
  event.modify()->description = ret.description;
  event.modify()->calendar =
      session_.find<Calendars>().where("id = ?").bind(ret.calendar_id);

  event.modify()->time_start = Wt::WDateTime::fromString(ret.begin_point);
  event.modify()->time_end = Wt::WDateTime::fromString(ret.end_point);

  transaction.commit();
}
const Event& EventDbManager::get(int event_id) {
  dbo::Transaction transaction(session_);

  Event ret;

  dbo::ptr<Events> event = session_.find<Events>().where("id = ?").bind(event_id);
  if (!event) {
    ret.name = "error";
    return ret;
  }
  ret.name = event->name;

  ret.description = event->description;

  std::cout << event->calendar.id() << std::endl;
  ret.calendar_id = event->calendar.id();

  ret.begin_point = event->time_start.toString().toUTF8();
  ret.end_point = event->time_end.toString().toUTF8();

  transaction.commit();

  return ret;
}
