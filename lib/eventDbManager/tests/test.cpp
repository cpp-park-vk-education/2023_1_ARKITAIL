#include "eventDbManager.hpp"
#include "mainModel.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// Создание мока для Session
class MockSession : public dbo::Session {

public:
  MOCK_METHOD(int, Add, (const RetEvent &));
  MOCK_METHOD(void, Remove, (int));
  MOCK_METHOD(void, Update, (const RetEvent &));
  MOCK_METHOD(RetEvent, Get, (int));
};
bool operator==(const RetEvent &lhs, const RetEvent &rhs) {
  return lhs.name == rhs.name && lhs.t_start == rhs.t_start &&
         lhs.t_end == rhs.t_end && lhs.description == rhs.description &&
         lhs.calendar_id == rhs.calendar_id;
};
// Тестирование метода Add класса EventManager с использованием мока Session
TEST(EventManagerTest, AddEvent) {

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

  //session.createTables();

  typedef dbo::collection<dbo::ptr<Events>> Eventss;
  Eventss eventss = session.find<Events>();

  // Создание объекта EventManager с использованием мока Session
  EventManager manager(session);

  // Создание тестовых данных
  RetEvent ret;
  ret.name = "Test7 Event";
  ret.t_start = "Wed Aug 29 23:15:43 2007";
  ret.t_end = "Wed Aug 29 23:15:43 2008";
  ret.description = "Test Description";
  ret.calendar_id = 2;

  using ::testing::Return;
  // Ожидание вызова метода Add у мока Session с передачей события
  // EXPECT_CALL(session, Add(testing::_));

  int eventId = manager.Add(ret);

  EXPECT_NE(eventId, -1);
  transaction.commit();
}

TEST(EventManagerTest, RemoveAndGetEvent) {

  // Создание мок-объекта Session
  MockSession session;
  std::unique_ptr<dbo::backend::Postgres> pg{new dbo::backend::Postgres(
      "host=localhost port=5432 dbname=for_project_ARKITAIL user=antiho "
      "password=qwerty")};
  session.setConnection(std::move(pg));
  dbo::Transaction transaction(session);
  session.mapClass<Calendars>("Calendars");
  session.mapClass<Users>("Users");

  session.mapClass<Events>("Events");

  // session.createTables();

  typedef dbo::collection<dbo::ptr<Events>> Eventss;
  Eventss eventss = session.find<Events>();

  // Создание объекта EventManager с использованием мока Session
  EventManager manager(session);

  // Создание тестовых данных
  int id = 100;

  using ::testing::Return;
  // Ожидание вызова метода Add у мока Session с передачей события
  // EXPECT_CALL(session, Add(testing::_));
  manager.Remove(id);
  RetEvent ret;
  ret = manager.Get(id);
  EXPECT_EQ(ret.name, "error");
  transaction.commit();
}


TEST(EventManagerTest, UpdateAndGetEvent) {

  // Создание мок-объекта Session
  MockSession session;
  std::unique_ptr<dbo::backend::Postgres> pg{new dbo::backend::Postgres(
      "host=localhost port=5432 dbname=for_project_ARKITAIL user=antiho "
      "password=qwerty")};
  session.setConnection(std::move(pg));
  dbo::Transaction transaction(session);
  session.mapClass<Calendars>("Calendars");
  session.mapClass<Users>("Users");

  session.mapClass<Events>("Events");

  //session.createTables();

  typedef dbo::collection<dbo::ptr<Events>> Eventss;
  Eventss eventss = session.find<Events>();

  // Создание объекта EventManager с использованием мока Session
  EventManager manager(session);
    int id;
  std::cin >> id;
  RetEvent ret;
  ret.event_id = id;
  ret.name = "Test Update Event";
  ret.t_start = "Wed Aug 29 2008";
  ret.t_end = "Wed Aug 29 2007";
  ret.description = "Test Description";
  ret.calendar_id = 1;
  // Создание тестовых данных


  using ::testing::Return;
  // Ожидание вызова метода Add у мока Session с передачей события
  // EXPECT_CALL(session, Add(testing::_));
  manager.Update(ret);
  ret = manager.Get(id);
  EXPECT_NE(ret.name, "error");  transaction.commit();
}