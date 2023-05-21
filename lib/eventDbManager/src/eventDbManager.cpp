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

  std::tm tm_start = {ret.t_start[0], ret.t_start[1], ret.t_start[2],
                      ret.t_start[3], ret.t_start[4], ret.t_start[5] - 1900};
  event->time_start = std::mktime(&tm_start);

  std::tm tm_end = {ret.t_end[0], ret.t_end[1], ret.t_end[2],
                    ret.t_end[3], ret.t_end[4], ret.t_end[5] - 1900};
  event->time_end = std::mktime(&tm_end);

  dbo::ptr<events> eventPtr = session_.add(std::move(event));
  eventPtr = session_.find<events>().where("name = ?").bind("Test1 Event");
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

  std::tm tm_start = {ret.t_start[0], ret.t_start[1], ret.t_start[2],
                      ret.t_start[3], ret.t_start[4], ret.t_start[5] - 1900};
  event.modify()->time_start = std::mktime(&tm_start);

  std::tm tm_end = {ret.t_end[0], ret.t_end[1], ret.t_end[2],
                    ret.t_end[3], ret.t_end[4], ret.t_end[5] - 1900};
  event.modify()->time_end = std::mktime(&tm_end);

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

  std::tm tm_res_start = *std::localtime(&event->time_start);

  ret.t_start = {tm_res_start.tm_sec,  tm_res_start.tm_min,
                 tm_res_start.tm_hour, tm_res_start.tm_mday,
                 tm_res_start.tm_mon,  tm_res_start.tm_year + 1900};
  std::tm tm_res_end = *std::localtime(&event->time_end);

  ret.t_end = {tm_res_end.tm_sec,  tm_res_end.tm_min,
               tm_res_end.tm_hour, tm_res_end.tm_mday,
               tm_res_end.tm_mon,  tm_res_end.tm_year + 1900};

  transaction.commit();

  return ret;
}
