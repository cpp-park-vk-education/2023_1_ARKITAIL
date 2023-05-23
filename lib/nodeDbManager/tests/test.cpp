#include "nodeDbManager.hpp"
#include "mainModel.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// Создание мока для Session
class MockSession : public dbo::Session {

public:
  MOCK_METHOD(int, Add, (const RetNode &));
  MOCK_METHOD(void, Remove, (int));
  MOCK_METHOD(void, Update, (const RetNode &));
  MOCK_METHOD(RetNode, Get, (int));
};
bool operator==(const RetNode &lhs, const RetNode &rhs) {
  return lhs.parent_id == rhs.parent_id && lhs.type == rhs.type &&
         lhs.resource_id == rhs.resource_id;
};
TEST(NodeManagerTest, AddNodeAndTag) {

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

  typedef dbo::collection<dbo::ptr<Nodes>> Nodess;
  Nodess eventss = session.find<Nodes>();

  typedef dbo::collection<dbo::ptr<Calendars>> Calendarss;
  Calendarss clendarss = session.find<Calendars>();

  // Создание объекта EventManager с использованием мока Session
  NodeManager manager(session);
  // Создание тестовых данных
  NodeType type = NodeType::PUBLIC_CALENDAR;
  RetNode ret;
  ret.parent_id = 4;
  ret.type = type;
  ret.resource_id = 1;

  RetTag rett;
  rett.tag_id = 1;
  rett.name = "Test Tag";
  
  using ::testing::Return;
  // Ожидание вызова метода add у мока Session с передачей события
  // EXPECT_CALL(session, add(testing::_));

  int nodeId = manager.Add(ret);
  manager.Tag(3, rett);

  EXPECT_NE(nodeId, -1);
  transaction.commit();
}

// TEST(CalendarManagerTest, RemoveAndGetCalendar) {

//   // Создание мок-объекта Session
//   MockSession session;
//   std::unique_ptr<dbo::backend::Postgres> pg{new dbo::backend::Postgres(
//       "host=localhost port=5432 dbname=for_project_ARKITAIL user=antiho "
//       "password=qwerty")};
//   session.setConnection(std::move(pg));
//   dbo::Transaction transaction{session};
//   session.mapClass<Calendars>("Calendars");
//   session.mapClass<Users>("Users");
//   session.mapClass<Events>("Events");
//   session.mapClass<Nodes>("Nodes");
//   session.mapClass<Tags>("Tags");

//   // session.createTables();

//   typedef dbo::collection<dbo::ptr<Events>> Eventss;
//   Eventss eventss = session.find<Events>();

//   typedef dbo::collection<dbo::ptr<Calendars>> Calendarss;
//   Calendarss clendarss = session.find<Calendars>();

//   // Создание объекта EventManager с использованием мока Session
//   CalendarManager manager(session);

//   int id = 100;

//   using ::testing::Return;
//   // Ожидание вызова метода add у мока Session с передачей события
//   // EXPECT_CALL(session, add(testing::_));
//   manager.Remove(id);
//   RetCalen ret;
//   ret = manager.Get(id);
//   EXPECT_EQ(ret.name, "error");
//   transaction.commit();
// }

// TEST(CalendarManagerTest, UpdateAndGetEvent) {
//   // Создание мок-объекта Session
//   MockSession session;
//   std::unique_ptr<dbo::backend::Postgres> pg{new dbo::backend::Postgres(
//       "host=localhost port=5432 dbname=for_project_ARKITAIL user=antiho "
//       "password=qwerty")};
//   session.setConnection(std::move(pg));
//   dbo::Transaction transaction{session};
//   session.mapClass<Calendars>("Calendars");
//   session.mapClass<Users>("Users");
//   session.mapClass<Events>("Events");
//   session.mapClass<Nodes>("Nodes");
//   session.mapClass<Tags>("Tags");

//   // session.createTables();

//   typedef dbo::collection<dbo::ptr<Events>> Eventss;
//   Eventss eventss = session.find<Events>();

//   typedef dbo::collection<dbo::ptr<Calendars>> Calendarss;
//   Calendarss clendarss = session.find<Calendars>();

//   // Создание объекта EventManager с использованием мока Session
//   CalendarManager manager(session);

//   // Создание тестовых данных
//   int id;
//   std::cin >> id;
//   RetCalen ret;
//   ret.name = "Test3 Update Calendar";
//   ret.user_id = 1;
//   ret.node_id = 1;
//   ret.description = "Test Description";

//   using ::testing::Return;
//   // Ожидание вызова метода add у мока Session с передачей события
//   // EXPECT_CALL(session, add(testing::_));

//   manager.Update(ret);
//   ret = manager.Get(id);
//   EXPECT_NE(ret.name, "error");
//   transaction.commit();
// }

// TEST(CalendarManagerTest, GetEventFromCalendar) {
//   // Создание мок-объекта Session
//   MockSession session;
//   std::unique_ptr<dbo::backend::Postgres> pg{new dbo::backend::Postgres(
//       "host=localhost port=5432 dbname=for_project_ARKITAIL user=antiho "
//       "password=qwerty")};
//   session.setConnection(std::move(pg));
//   dbo::Transaction transaction{session};
//   session.mapClass<Calendars>("Calendars");
//   session.mapClass<Users>("Users");
//   session.mapClass<Events>("Events");
//   session.mapClass<Nodes>("Nodes");
//   session.mapClass<Tags>("Tags");

//   // session.createTables();

//   typedef dbo::collection<dbo::ptr<Events>> Eventss;
//   Eventss eventss = session.find<Events>();

//   typedef dbo::collection<dbo::ptr<Calendars>> Calendarss;
//   Calendarss clendarss = session.find<Calendars>();

//   // Создание объекта EventManager с использованием мока Session
//   CalendarManager manager(session);

//   // Создание тестовых данных
//   int id;
//   std::cin >> id;

//   RetEvent ret;
//   std::vector<RetEvent> v;

//   using ::testing::Return;
//   // Ожидание вызова метода add у мока Session с передачей события
//   // EXPECT_CALL(session, add(testing::_));

//   v = manager.GetEvents(id);
//   EXPECT_EQ(v.size(), 1);
//   transaction.commit();
// }