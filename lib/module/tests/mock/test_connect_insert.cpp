#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>

using namespace testing;
using namespace Wt::Dbo;

// Определение класса, который будет использоваться для создания mock-объектов
class MockPostgresConnection : public PostgresConnection {
public:
    MOCK_METHOD(void, execute, (const std::string&), (override));
    MOCK_METHOD(void, prepare, (const std::string&, const std::string&), (override));
    // Добавьте другие методы, которые будут использоваться в тесте
};

TEST(PostgresTest, InsertRecord) {
    // Создание mock-объекта для подключения к базе данных
    auto conn = std::make_unique<MockPostgresConnection>();
    session s;

    // Установка mock-объекта в качестве backend-а для сессии
    s.setConnection(std::move(conn));

    // Подготовка данных для добавления в таблицу
    const std::string login = "John";
    const std::string email = "john@example.com";
    const std::string password = "Secret";
    const std::vector<unsigned char> avatar = read_file("avatar2.jpg");

    

    // Создание mock-запроса
    EXPECT_CALL(*conn, execute("INSERT INTO users (name, email) VALUES ('John', 'john@example.com')"))
        .Times(1);

    // Выполнение запроса
    s << "INSERT INTO users (name, email) VALUES (?, ?)" << name << email;

    // Убедимся, что mock-объект был вызван
    Mock::VerifyAndClearExpectations(conn.get());
}
