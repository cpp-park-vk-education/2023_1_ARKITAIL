#include "calendarDbManager.hpp"
#include "mainModel.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// Создание мока для Session
class MockSession : public dbo::Session {

public:
  MOCK_METHOD(int, Add, (const RetCalen &));
  MOCK_METHOD(void, Remove, (int));
  MOCK_METHOD(void, Update, (const RetCalen &));
  MOCK_METHOD(RetCalen, Get, (int));
};
bool operator==(const RetCalen &lhs, const RetCalen &rhs) {
  return lhs.name == rhs.name && lhs.user_id == rhs.user_id && lhs.description == rhs.description &&
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
  session.mapClass<Calendars>("Calendars");
  session.mapClass<Users>("Users");
  session.mapClass<Events>("Events");
  session.mapClass<Nodes>("Nodes");
  session.mapClass<Tags>("Tags");

  //session.createTables();

  typedef dbo::collection<dbo::ptr<Events>> Eventss;
  Eventss eventss = session.find<Events>();

  typedef dbo::collection<dbo::ptr<Calendars>> Calendarss;
  Calendarss clendarss = session.find<Calendars>();

  // Создание объекта EventManager с использованием мока Session
  CalendarManager manager(session);

  // Создание тестовых данных
  RetCalen ret;
  ret.name = "Test5 Calendar";
  ret.user_id = 1;
  ret.description = "Test Description";
  ret.node_id = 1;

  using ::testing::Return;
  // Ожидание вызова метода add у мока Session с передачей события
  // EXPECT_CALL(session, add(testing::_));

  int calendarId = manager.Add(ret);

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
  session.mapClass<Calendars>("Calendars");
  session.mapClass<Users>("Users");
  session.mapClass<Events>("Events");
  session.mapClass<Nodes>("Nodes");
  session.mapClass<Tags>("Tags");

  // session.createTables();

  typedef dbo::collection<dbo::ptr<Events>> Eventss;
  Eventss eventss = session.find<Events>();

  typedef dbo::collection<dbo::ptr<Calendars>> Calendarss;
  Calendarss clendarss = session.find<Calendars>();

  // Создание объекта EventManager с использованием мока Session
  CalendarManager manager(session);

  int id = 100;

  using ::testing::Return;
  // Ожидание вызова метода add у мока Session с передачей события
  // EXPECT_CALL(session, add(testing::_));
  manager.Remove(id);
  RetCalen ret;
  ret = manager.Get(id);
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
  session.mapClass<Calendars>("Calendars");
  session.mapClass<Users>("Users");
  session.mapClass<Events>("Events");
  session.mapClass<Nodes>("Nodes");
  session.mapClass<Tags>("Tags");

  // session.createTables();

  typedef dbo::collection<dbo::ptr<Events>> Eventss;
  Eventss eventss = session.find<Events>();

  typedef dbo::collection<dbo::ptr<Calendars>> Calendarss;
  Calendarss clendarss = session.find<Calendars>();

  // Создание объекта EventManager с использованием мока Session
  CalendarManager manager(session);

  // Создание тестовых данных
  int id;
  std::cin >> id;
  RetCalen ret;
  ret.name = "Test3 Update Calendar";
  ret.user_id = 1;
  ret.description = "Test Description";
  ret.node_id = 1;

  using ::testing::Return;
  // Ожидание вызова метода add у мока Session с передачей события
  // EXPECT_CALL(session, add(testing::_));

  manager.Update(ret);
  ret = manager.Get(id);
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
  session.mapClass<Calendars>("Calendars");
  session.mapClass<Users>("Users");
  session.mapClass<Events>("Events");
  session.mapClass<Nodes>("Nodes");
  session.mapClass<Tags>("Tags");

  // session.createTables();

  typedef dbo::collection<dbo::ptr<Events>> Eventss;
  Eventss eventss = session.find<Events>();

  typedef dbo::collection<dbo::ptr<Calendars>> Calendarss;
  Calendarss clendarss = session.find<Calendars>();

  // Создание объекта EventManager с использованием мока Session
  CalendarManager manager(session);

  // Создание тестовых данных
  int id;
  std::cin >> id;

  RetEvent ret;
  std::vector<RetEvent> v;

  using ::testing::Return;
  // Ожидание вызова метода add у мока Session с передачей события
  // EXPECT_CALL(session, add(testing::_));

  v = manager.GetEvents(id);
  EXPECT_EQ(v.size(), 1);
  transaction.commit();
}