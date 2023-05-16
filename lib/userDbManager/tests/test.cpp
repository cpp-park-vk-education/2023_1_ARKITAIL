#include <gtest/gtest.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/Impl.h>
#include <Wt/Dbo/backend/Postgres.h>
#include <string>
//#include "include/User_db_manager.hpp"

namespace dbo = Wt::Dbo;



class Person {
public:
    std::string name;
    int age;

    template<class Action>
    void persist(Action& a)
    {
        dbo::field(a, name, "name");
        dbo::field(a, age, "age");
    }
};



// // Тест на вставку данных в таблицу
// TEST_F(MyDatabaseTest, TestInsertData){
//     std::unique_ptr<dbo::backend::Postgres> pg {new dbo::backend::Postgres("host=localhost port=5432 dbname=test user=antiho password=qwerty")};
//     dbo::Session session;
//     session.setConnection(std::move(pg));

//     session.mapClass<Person>("Person");
//     session.createTables(); //already create
//     // Создаем экземпляр класса схемы таблицы
//     Wt::Dbo::Transaction transaction(session);
//     std::unique_ptr<Person> person = std::make_unique<Person>();

//     // Задаем значения полей
//     person->name = "Ivan";
//     person->age = 25;

//     // Вставляем данные в таблицу
//     session.add(std::move(person));
//     transaction.commit();

//     // Проверяем, что данные были успешно вставлены в таблицу
//     Wt::Dbo::Transaction readTransaction(session);
//     Wt::Dbo::collection<std::unique_ptr<Person>> people = session.find<Person>();
//     ASSERT_EQ(1u, people.size());
//     ASSERT_EQ("Ivan", people[0]->name);
//     ASSERT_EQ(25, people[0]->age);
// }

