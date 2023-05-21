#include "eventDbManager.hpp"
#include "mainModel.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <random>

// Создание мока для Session
class MockSession : public dbo::Session {

public:
  MOCK_METHOD(int, add, (const Ret_Event &));
  MOCK_METHOD(void, removeEvent, (int));
  MOCK_METHOD(void, updateEvent, (const Ret_Event &));
  MOCK_METHOD(Ret_Event, getEvent, (int));
};
bool operator==(const Ret_Event &lhs, const Ret_Event &rhs) {
  return lhs.name == rhs.name && lhs.t_start == rhs.t_start &&
         lhs.t_end == rhs.t_end && lhs.description == rhs.description &&
         lhs.calendar_id == rhs.calendar_id;
};
// Тестирование метода add класса EventManager с использованием мока Session
TEST(EventManagerTest, AddEvent) {

  // Создание мок-объекта Session
  MockSession session;
  std::unique_ptr<dbo::backend::Postgres> pg{new dbo::backend::Postgres(
      "host=localhost port=5432 dbname=for_project_ARKITAIL user=antiho "
      "password=qwerty")};
  session.setConnection(std::move(pg));
  dbo::Transaction transaction{session};
  session.mapClass<calendars>("calendars");

  session.mapClass<events>("events");

  //session.createTables();

  typedef dbo::collection<dbo::ptr<events>> Events;
  Events eventss = session.find<events>();

  // Создание объекта EventManager с использованием мока Session
  EventManager manager(session);

  // Создание тестовых данных
  Ret_Event ret;
  ret.name = "Test2 Event";
  ret.t_start = {1, 2, 3, 4, 5, 2000};
  ret.t_end = {7, 8, 9, 10, 11, 2000};
  ret.description = "Test Description";
  ret.calendar_id = 1;

  using ::testing::Return;
  // Ожидание вызова метода add у мока Session с передачей события
  // EXPECT_CALL(session, add(testing::_));

  int eventId = manager.add(ret);

  EXPECT_NE(eventId, -1);
  transaction.commit();
}

TEST(EventManagerTest1, RemoveAndGetEvent) {

  // Создание мок-объекта Session
  MockSession session;
  std::unique_ptr<dbo::backend::Postgres> pg{new dbo::backend::Postgres(
      "host=localhost port=5432 dbname=for_project_ARKITAIL user=antiho "
      "password=qwerty")};
  session.setConnection(std::move(pg));
  dbo::Transaction transaction(session);
  session.mapClass<calendars>("calendars");

  session.mapClass<events>("events");

  // session.createTables();

  typedef dbo::collection<dbo::ptr<events>> Events;
  Events eventss = session.find<events>();

  // Создание объекта EventManager с использованием мока Session
  EventManager manager(session);

  // Создание тестовых данных
  int id;
  std::cin >> id;

  using ::testing::Return;
  // Ожидание вызова метода add у мока Session с передачей события
  // EXPECT_CALL(session, add(testing::_));
  manager.remove(id);
  Ret_Event ret;
  ret = manager.get(id);
  EXPECT_EQ(ret.name, "error");
  transaction.commit();
}


TEST(EventManagerTest1, UpdateAndGetEvent) {

  // Создание мок-объекта Session
  MockSession session;
  std::unique_ptr<dbo::backend::Postgres> pg{new dbo::backend::Postgres(
      "host=localhost port=5432 dbname=for_project_ARKITAIL user=antiho "
      "password=qwerty")};
  session.setConnection(std::move(pg));
  dbo::Transaction transaction(session);
  session.mapClass<calendars>("calendars");

  session.mapClass<events>("events");

  // session.createTables();

  typedef dbo::collection<dbo::ptr<events>> Events;
  Events eventss = session.find<events>();

  // Создание объекта EventManager с использованием мока Session
  EventManager manager(session);
    int id;
  std::cin >> id;
  Ret_Event ret;
  ret.event_id = id;
  ret.name = "Test Update Event";
  ret.t_start = {1, 2, 3, 4, 5, 2000};
  ret.t_end = {7, 8, 9, 10, 11, 2000};
  ret.description = "Test Description";
  ret.calendar_id = 1;
  // Создание тестовых данных


  using ::testing::Return;
  // Ожидание вызова метода add у мока Session с передачей события
  // EXPECT_CALL(session, add(testing::_));
  manager.update(ret);
  ret = manager.get(id);
  EXPECT_NE(ret.name, "error");  transaction.commit();
}