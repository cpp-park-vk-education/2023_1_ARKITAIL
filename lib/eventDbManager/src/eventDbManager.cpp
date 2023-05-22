#include "eventDbManager.hpp"

// time_start и time_end передаются в виде "0, 0, 0, 14, 4, 2023 - 1900",
// где это сек, мин, час, д, мес, год
int EventManager::Add(RetEvent &ret) {
  dbo::Transaction transaction(session_);

  std::unique_ptr<Events> event{new Events()};
  event->name = ret.name;
  event->description = ret.description;
  event->calendar =
      session_.find<Calendars>().where("id = ?").bind(ret.calendar_id);
  Wt::WString time_help =  Wt::WString::fromUTF8(ret.t_start);
  event->time_start = Wt::WDateTime::fromString(time_help);
  std::cout << time_help << std::endl;
  time_help =  Wt::WString::fromUTF8(ret.t_end);
  event->time_end = Wt::WDateTime::fromString(ret.t_end);

  dbo::ptr<Events> eventPtr = session_.add(std::move(event));
  session_.flush();
  transaction.commit();
  id_ = eventPtr.id();
  return id_;
}

void EventManager::Remove(int id) {
  dbo::Transaction transaction(session_);

  dbo::ptr<Events> event = session_.find<Events>().where("id = ?").bind(id);
  if (!event) {
    return;
  }
  event.remove();
  transaction.commit();
}

void EventManager::Update(RetEvent &ret) {
  dbo::Transaction transaction(session_);

  dbo::ptr<Events> event =
      session_.find<Events>().where("id = ?").bind(ret.event_id);
  if (!event) {
    return;
  }
  event.modify()->name = ret.name;
  event.modify()->description = ret.description;
  event.modify()->calendar =
      session_.find<Calendars>().where("id = ?").bind(ret.calendar_id);

  event.modify()->time_start = Wt::WDateTime::fromString(ret.t_start);
  event.modify()->time_end = Wt::WDateTime::fromString(ret.t_end);

  transaction.commit();
}
RetEvent EventManager::Get(int id) {
  dbo::Transaction transaction(session_);

  RetEvent ret;

  dbo::ptr<Events> event = session_.find<Events>().where("id = ?").bind(id);
  if (!event) {
    ret.name = "error";
    return ret;
  }
  ret.name = event->name;

  ret.description = event->description;

  std::cout << event->calendar.id() << std::endl;
  ret.calendar_id = event->calendar.id();

  ret.t_start = event->time_start.toString().toUTF8();
  ret.t_end = event->time_end.toString().toUTF8();

  transaction.commit();

  return ret;
}
