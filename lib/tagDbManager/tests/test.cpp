#include "tagDbManager.hpp"
#include "mainModel.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// Создание мока для Session
class MockSession : public dbo::Session {

public:
  MOCK_METHOD(int, Add, (const RetTag &));
  MOCK_METHOD(void, Remove, (int));
  MOCK_METHOD(RetTag, Get, (int));
};
bool operator==(const RetTag &lhs, const RetTag &rhs) {
  return lhs.name == rhs.name;
};
TEST(TagManagerTest, AddTag) {

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

  typedef dbo::collection<dbo::ptr<Tags>> Tagss;
  Tagss clendarss = session.find<Tags>();

  // Создание объекта EventManager с использованием мока Session
  TagManager manager(session);
  // Создание тестовых данных
  RetTag ret;
  ret.name = "Test Tag";
  
  using ::testing::Return;
  // Ожидание вызова метода add у мока Session с передачей события
  // EXPECT_CALL(session, add(testing::_));

  int tagId = manager.Add(ret);

  EXPECT_NE(tagId, -1);
  transaction.commit();
}