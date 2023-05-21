#include "calendarDbManager.hpp"

int CalendarManager::add(Ret_Calen &ret) {
  dbo::Transaction transaction(session_);

  std::unique_ptr<calendars> calendar{new calendars()};
  calendar->name = ret.name;
  calendar->description = ret.description;
  //calendar->node = session_.find<nodes>().where("id = ?").bind(ret.node_id);
  //calendar->user = session_.find<users>().where("id = ?").bind(ret.user_id);

  dbo::ptr<calendars> calendarPtr = session_.add(std::move(calendar));
  calendarPtr = session_.find<calendars>().where("name = ?").bind(ret.name);

  id = calendarPtr.id();
  transaction.commit();

  return id;
}

void CalendarManager::remove(const int id) {
  dbo::Transaction transaction(session_);

  dbo::ptr<calendars> calendar =
      session_.find<calendars>().where("id = ?").bind(id);

  calendar.remove();
  transaction.commit();
}

void CalendarManager::update(Ret_Calen &ret) {
  dbo::Transaction transaction(session_);

  dbo::ptr<calendars> calendar =
      session_.find<calendars>().where("name = ?").bind(ret.name);

  calendar.modify()->name = ret.name;
  calendar.modify()->description = ret.description;
  //calendar.modify()->node =
  //    session_.find<nodes>().where("id = ?").bind(ret.node_id);
  //calendar.modify()->user =
  //    session_.find<users>().where("id = ?").bind(ret.user_id);

  transaction.commit();
}
Ret_Calen CalendarManager::get(const int id) {
  dbo::Transaction transaction(session_);

  Ret_Calen ret;
  dbo::ptr<calendars> calendar =
      session_.find<calendars>().where("id = ?").bind(id);
  ret.name = calendar->name;
  ret.description = calendar->description;
  //ret.node_id = calendar->node.id();
  //ret.user_id = calendar->user.id();

  transaction.commit();

  return ret;
}

std::vector<Ret_Event> CalendarManager::getEvents(const int id) {

  Ret_Event ret;
  std::vector<Ret_Event> v;

  dbo::Transaction transaction(session_);
  dbo::ptr<calendars> calendar =
      session_.find<calendars>().where("id = ?").bind(id);
  dbo::collection<dbo::ptr<events>> event =
        session_.find<events>().where("calendar_id = ?").bind(id);

  for (const dbo::ptr<events>& eve : event) {

        ret.name = eve->name;
    ret.description = eve->description;
    //ret.calendar_id = eve->calendar.id();
    std::tm tm_res_start = *std::localtime(&eve->time_start);

    ret.t_start = {tm_res_start.tm_sec,  tm_res_start.tm_min,
                   tm_res_start.tm_hour, tm_res_start.tm_mday,
                   tm_res_start.tm_mon,  tm_res_start.tm_year + 1900};
    std::tm tm_res_end = *std::localtime(&eve->time_end);

    ret.t_end = {tm_res_end.tm_sec,  tm_res_end.tm_min,
                 tm_res_end.tm_hour, tm_res_end.tm_mday,
                 tm_res_end.tm_mon,  tm_res_end.tm_year + 1900};

    v.push_back(ret);
  }

  transaction.commit();

  return v;
}
