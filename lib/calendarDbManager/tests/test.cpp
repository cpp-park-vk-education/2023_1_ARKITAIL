#include "calendarDbManager.hpp"
#include "mainModel.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// Создание мока для Session
class MockSession : public dbo::Session {

public:
  MOCK_METHOD(int, addCalendar, (const Ret_Event &));
  MOCK_METHOD(void, removeCalendar, (int));
  MOCK_METHOD(void, updateCalendar, (const Ret_Event &));
  MOCK_METHOD(Ret_Event, getCalendar, (int));
};
bool operator==(const Ret_Calen &lhs, const Ret_Calen &rhs) {
  return lhs.name == rhs.name && lhs.node_id == rhs.node_id &&
         lhs.user_id == rhs.user_id && lhs.description == rhs.description &&
         lhs.calendar_id == rhs.calendar_id;
};
TEST(CalendarManagerTest, AddCalendar) {

  // Создание мок-объекта Session
  MockSession session;
  std::unique_ptr<dbo::backend::Postgres> pg{new dbo::backend::Postgres(
      "host=localhost port=5432 dbname=for_project_ARKITAIL user=antiho "
      "password=qwerty")};
  session.setConnection(std::move(pg));
  dbo::Transaction transaction{session};
  session.mapClass<calendars>("calendars");
  session.mapClass<users>("users");
  session.mapClass<events>("events");
  session.mapClass<nodes>("nodes");
  session.mapClass<tags>("tags");

  // session.createTables();

  typedef dbo::collection<dbo::ptr<events>> Events;
  Events eventss = session.find<events>();

  typedef dbo::collection<dbo::ptr<calendars>> Calendars;
  Calendars clendarss = session.find<calendars>();

  // Создание объекта EventManager с использованием мока Session
  CalendarManager manager(session);

  // Создание тестовых данных
  Ret_Calen ret;
  ret.name = "Test5 Calendar";
  ret.user_id = 1;
  ret.node_id = 1;
  ret.description = "Test Description";

  using ::testing::Return;
  // Ожидание вызова метода add у мока Session с передачей события
  // EXPECT_CALL(session, add(testing::_));

  int calendarId = manager.add(ret);

  EXPECT_NE(calendarId, -1);
  transaction.commit();
}

TEST(CalendarManagerTest, RemoveAndGetCalendar) {

  // Создание мок-объекта Session
  MockSession session;
  std::unique_ptr<dbo::backend::Postgres> pg{new dbo::backend::Postgres(
      "host=localhost port=5432 dbname=for_project_ARKITAIL user=antiho "
      "password=qwerty")};
  session.setConnection(std::move(pg));
  dbo::Transaction transaction{session};
  session.mapClass<calendars>("calendars");
  session.mapClass<users>("users");
  session.mapClass<events>("events");
  session.mapClass<nodes>("nodes");
  session.mapClass<tags>("tags");

  // session.createTables();

  typedef dbo::collection<dbo::ptr<events>> Events;
  Events eventss = session.find<events>();

  typedef dbo::collection<dbo::ptr<calendars>> Calendars;
  Calendars clendarss = session.find<calendars>();

  // Создание объекта EventManager с использованием мока Session
  CalendarManager manager(session);

  int id = 100;

  using ::testing::Return;
  // Ожидание вызова метода add у мока Session с передачей события
  // EXPECT_CALL(session, add(testing::_));
  manager.remove(id);
  Ret_Calen ret;
  ret = manager.get(id);
  EXPECT_EQ(ret.name, "error");
  transaction.commit();
}

TEST(CalendarManagerTest, UpdateAndGetEvent) {
  // Создание мок-объекта Session
  MockSession session;
  std::unique_ptr<dbo::backend::Postgres> pg{new dbo::backend::Postgres(
      "host=localhost port=5432 dbname=for_project_ARKITAIL user=antiho "
      "password=qwerty")};
  session.setConnection(std::move(pg));
  dbo::Transaction transaction{session};
  session.mapClass<calendars>("calendars");
  session.mapClass<users>("users");
  session.mapClass<events>("events");
  session.mapClass<nodes>("nodes");
  session.mapClass<tags>("tags");

  // session.createTables();

  typedef dbo::collection<dbo::ptr<events>> Events;
  Events eventss = session.find<events>();

  typedef dbo::collection<dbo::ptr<calendars>> Calendars;
  Calendars clendarss = session.find<calendars>();

  // Создание объекта EventManager с использованием мока Session
  CalendarManager manager(session);

  // Создание тестовых данных
  int id;
  std::cin >> id;
  Ret_Calen ret;
  ret.name = "Test3 Update Calendar";
  ret.user_id = 1;
  ret.node_id = 1;
  ret.description = "Test Description";

  using ::testing::Return;
  // Ожидание вызова метода add у мока Session с передачей события
  // EXPECT_CALL(session, add(testing::_));

  manager.update(ret);
  ret = manager.get(id);
  EXPECT_NE(ret.name, "error");
  transaction.commit();
}

TEST(CalendarManagerTest, GetEventFromCalendar) {
  // Создание мок-объекта Session
  MockSession session;
  std::unique_ptr<dbo::backend::Postgres> pg{new dbo::backend::Postgres(
      "host=localhost port=5432 dbname=for_project_ARKITAIL user=antiho "
      "password=qwerty")};
  session.setConnection(std::move(pg));
  dbo::Transaction transaction{session};
  session.mapClass<calendars>("calendars");
  session.mapClass<users>("users");
  session.mapClass<events>("events");
  session.mapClass<nodes>("nodes");
  session.mapClass<tags>("tags");

  // session.createTables();

  typedef dbo::collection<dbo::ptr<events>> Events;
  Events eventss = session.find<events>();

  typedef dbo::collection<dbo::ptr<calendars>> Calendars;
  Calendars clendarss = session.find<calendars>();

  // Создание объекта EventManager с использованием мока Session
  CalendarManager manager(session);

  // Создание тестовых данных
  int id;
  std::cin >> id;

  Ret_Event ret;
  std::vector<Ret_Event> v;

  using ::testing::Return;
  // Ожидание вызова метода add у мока Session с передачей события
  // EXPECT_CALL(session, add(testing::_));

  v = manager.getEvents(id);
  EXPECT_EQ(v.size(), 7);
  transaction.commit();
}