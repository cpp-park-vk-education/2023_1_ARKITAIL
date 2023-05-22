#include "eventDbManager.hpp"

// time_start и time_end передаются в виде "0, 0, 0, 14, 4, 2023 - 1900",
// где это сек, мин, час, д, мес, год
int EventManager::add(Ret_Event &ret) {
  dbo::Transaction transaction(session_);

  std::unique_ptr<events> event{new events()};
  event->name = ret.name;
  event->description = ret.description;
  event->calendar =
      session_.find<calendars>().where("id = ?").bind(ret.calendar_id);
  Wt::WString time_help =  Wt::WString::fromUTF8(ret.t_start);
  event->time_start = Wt::WDateTime::fromString(time_help);
  std::cout << time_help << std::endl;
  time_help =  Wt::WString::fromUTF8(ret.t_end);
  event->time_end = Wt::WDateTime::fromString(ret.t_end);

  dbo::ptr<events> eventPtr = session_.add(std::move(event));
  session_.flush();
  transaction.commit();
  id = eventPtr.id();
  return id;
}

void EventManager::remove(const int id) {
  dbo::Transaction transaction(session_);

  dbo::ptr<events> event = session_.find<events>().where("id = ?").bind(id);
  if (!event) {
    return;
  }
  event.remove();
  transaction.commit();
}

void EventManager::update(Ret_Event &ret) {
  dbo::Transaction transaction(session_);

  dbo::ptr<events> event =
      session_.find<events>().where("id = ?").bind(ret.event_id);
  if (!event) {
    return;
  }
  event.modify()->name = ret.name;
  event.modify()->description = ret.description;
  event.modify()->calendar =
      session_.find<calendars>().where("id = ?").bind(ret.calendar_id);

  event.modify()->time_start = Wt::WDateTime::fromString(ret.t_start);
  event.modify()->time_end = Wt::WDateTime::fromString(ret.t_end);

  transaction.commit();
}
Ret_Event EventManager::get(const int id) {
  dbo::Transaction transaction(session_);

  Ret_Event ret;

  dbo::ptr<events> event = session_.find<events>().where("id = ?").bind(id);
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
