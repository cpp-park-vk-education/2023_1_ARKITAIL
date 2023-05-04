#include <gtest/gtest.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>
#include <string>
#include "User_db_manager.hpp"

namespace dbo = Wt::Dbo;

dbo::backend::Postgres backend("dbname=test user=antiho password=qwerty host=localhost port=5432");
dbo::Session session;
session.setConnection(backend);


// Тест на вставку данных в таблицу
TEST_F(MyDatabaseTest, TestInsertData)
{
    // Создаем экземпляр класса схемы таблицы
    dbo::Transaction transaction(session);
    std::unique_ptr<users> user = std::make_unique<users>();

    // Задаем значения полей
    user->name = "Ivan";
    user->age = 25;

    // Вставляем данные в таблицу
    session.add(std::move(user));
    transaction.commit();

    // Проверяем, что данные были успешно вставлены в таблицу
    dbo::Transaction readTransaction(session);
    dbo::collection<std::unique_ptr<users>> people = session.find<users>();
    ASSERT_EQ(1u, people.size());
    ASSERT_EQ("Ivan", people[0]->name);
    ASSERT_EQ(25, people[0]->age);
}

