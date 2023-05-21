// #include "libpq-fe.h"
// #include <pqxx/pqxx>
// #include <iostream>
// #include <string>

// // Задаем параметры подключения к базе данных
// const char* conninfo = "host=localhost port=5432 dbname=for_project_ARKITAIL
// user=antiho password=qwerty";

// // Устанавливаем соединение с базой данных
// PGconn* conn = PQconnectdb(conninfo);
// PGresult* res = NULL;

// int rows = NULL;
// int cols = NULL;

// void clearRes(){
//   PQclear(res);
//   res = NULL;
// }

// struct insert {
//     std::string table;
//     std::string id;
//     std::string columns;
//     std::string values;
// };

// struct selects{
//     std::string table;
// };

// void SelectFunction(const selects& p){
//   // Если соединение успешно установлено, продолжаем работу с базой данных
//   std::string s = "SELECT * FROM " + p.table;
//   const char* sql = s.c_str();

//   // Выполняем запрос по выводу значения всей таблицы
//   res = PQexec(conn, sql);

//   // Проверяем успешность выполнения запроса
//   if (PQresultStatus(res) != PGRES_TUPLES_OK)
//   {
//       // Выводим сообщение об ошибке
//       std::cout << "Query execution failed second: " << PQerrorMessage(conn)
//       << std::endl;

//       // Освобождаем ресурсы и выходим из приложения
//       PQclear(res);
//       PQfinish(conn);
//       return;
//   }

//   // Если запрос выполнен успешно, обрабатываем результаты
//   rows = PQntuples(res);
//   cols = PQnfields(res);
//   for (int i = 0; i < rows; i++)
//   {
//       for (int j = 0; j < cols; j++)
//       {
//           std::cout << PQgetvalue(res, i, j) << "\t";
//       }
//       std::cout << std::endl;
//   }

//   // Освобождаем ресурсы
//   PQclear(res);

//   // Закрываем соединение с базой данных
//   PQfinish(conn);
// }

// void InsertFunction(const insert& p){
//     std::string s = "INSERT INTO " + p.table + " ( " + p.id +  p.columns + "
//     ) VALUES ((SELECT COALESCE(MAX( " + p.id + " ), 0) FROM users) + 1, " +
//     p.values; const char* sql = s.c_str();
//     // Выполняем запрос по выводу значения всей таблицы
//     res = PQexec(conn, sql);

//     if (PQresultStatus(res) != PGRES_COMMAND_OK)
//     {
//         // Выводим сообщение об ошибке
//         std::cout << "Query execution failed first: " << PQerrorMessage(conn)
//         << std::endl;

//         // Освобождаем ресурсы и выходим из приложения
//         PQclear(res);
//         PQfinish(conn);
//         return;
//     }

//     std::cout << "all done!" << std::endl;

//     // Освобождаем ресурсы
//     PQclear(res);
// }

// int main(int argc, char* argv[]){
//   std::cout << "1" << std::endl;
//   // Проверяем успешность соединения
//   if (PQstatus(conn) != CONNECTION_OK)
//   {
//       // Выводим сообщение об ошибке
//       std::cout << "Connection to database failed: " << PQerrorMessage(conn)
//       << std::endl;
//       // Освобождаем ресурсы и выходим из приложения
//       PQfinish(conn);
//       return 1;
//   }
//   //Ввод данных из структуры
//   insert i = {"users", "user_id", ", name, email, password, avatar",
//   "'tester', 'test.l.2004@yandex.ru', 'qwerty', NULL);"}; InsertFunction(i);

//   //Вывод таблицы
//   selects s = {"users"};
//   SelectFunction(s);
// }

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>
#include <chrono>
#include <fstream>
#include <iterator>
#include <string>

std::vector<unsigned char> read_file(const std::string &filename) {
  std::ifstream file(filename, std::ios::binary);
  return std::vector<unsigned char>(std::istreambuf_iterator<char>(file),
                                    std::istreambuf_iterator<char>());
}

namespace dbo = Wt::Dbo;

class nodes;
class calendars;
class directories;

class users {
public:
  std::string login;
  std::string email;
  std::string password;
  std::vector<unsigned char> avatar;
  dbo::ptr<calendars> calendar;

  template <class Action> void persist(Action &a) {
    dbo::field(a, login, "login");
    dbo::field(a, email, "email");
    dbo::field(a, password, "password");
    dbo::field(a, avatar, "avatar");
    dbo::belongsTo(a, calendar, "calendar");
  }
};

enum class Type { Directory = 0, Calendar = 1, Mount = 2 };

class nodes {
public:
  Type type;
  dbo::ptr<nodes> parent;
  int resource_id;

  template <class Action> void persist(Action &a) {
    dbo::field(a, type, "type");
    dbo::belongsTo(a, parent, "parent");
    dbo::field(a, resource_id, "resource_id");
  }
};

class tags {
public:
  std::string name;
  dbo::collection<dbo::ptr<calendars>> calendar;

  template <class Action> void persist(Action &a) {
    dbo::field(a, name, "name");
    dbo::hasMany(a, calendar, dbo::ManyToMany, "calendar_tags");
  }
};

class directory {
public:
  std::string name;
  std::string description;
  dbo::ptr<nodes> node;

  template <class Action> void persist(Action &a) {
    dbo::field(a, name, "name");
    dbo::field(a, description, "description");
    dbo::belongsTo(a, node, "node");
  }
};

class events {
public:
  std::string name;
  std::time_t time_start;
  std::time_t time_end;
  std::string description;
  dbo::collection<dbo::ptr<calendars>> calendar;

  template <class Action> void persist(Action &a) {
    dbo::field(a, name, "name");
    dbo::field(a, time_start, "time_start");
    dbo::field(a, time_end, "time_end");
    dbo::field(a, description, "description");
    dbo::hasMany(a, calendar, dbo::ManyToOne, "event");
  }
};

class calendars {
public:
  dbo::collection<dbo::ptr<users>> user; // Owner
  dbo::collection<dbo::ptr<tags>> tag;   // tags
  bool visibility;                       // visibility
  std::string name;                      // name
  dbo::ptr<events> event;                // event
  dbo::ptr<nodes> node;                  // p_node

  template <class Action> void persist(Action &a) {
    dbo::field(a, name, "name");
    dbo::hasMany(a, user, dbo::ManyToOne, "calendar");
    dbo::belongsTo(a, event, "event");
    dbo::field(a, visibility, "visubility");
    dbo::hasMany(a, tag, dbo::ManyToMany, "calendar_tags");
    dbo::belongsTo(a, node, "node");
  }
};

struct check {
  int x;
};

// void enter_timed(dbo::Session& session){
//     std::unique_ptr<users> user{new users()};
//     user->name = "Joe";
//     user->email = "email@gmail.com";
//     user->password = "Secret";
//     user->avatar = read_file("avatar2.jpg");
//     dbo::ptr<users> userPtr = session.add(std::move(user));

//     std::unique_ptr<events> event{new events()};
//     event->name = "Joe";
//     event->time_start = NULL;
//     event->time_end = NULL;
//     event->description = "random description";
//     dbo::ptr<events> eventPtr = session.add(std::move(event));
// }

void connection(dbo::Session &session) {
  std::unique_ptr<dbo::backend::Postgres> pg{new dbo::backend::Postgres(
      "host=localhost port=5432 dbname=for_project_ARKITAIL user=antiho "
      "password=qwerty")};

  session.setConnection(std::move(pg));
}

time_t set_time_start() {
  std::tm timeinfo = {};
  timeinfo.tm_year =
      2023 - 1900; // год, отнимаем 1900 для приведения к формату tm
  timeinfo.tm_mon = 4; // май (нумерация месяцев начинается с 0)
  timeinfo.tm_mday = 2;  // день месяца
  timeinfo.tm_hour = 12; // часы
  timeinfo.tm_min = 30;  // минуты
  timeinfo.tm_sec = 0;   // секунды

  // преобразуем структуру tm в значение time_t
  time_t time = mktime(&timeinfo);
  return time;
}

time_t set_time_end() {
  std::tm timeinfo = {};
  timeinfo.tm_year =
      2024 - 1900; // год, отнимаем 1900 для приведения к формату tm
  timeinfo.tm_mon = 4; // май (нумерация месяцев начинается с 0)
  timeinfo.tm_mday = 2;  // день месяца
  timeinfo.tm_hour = 12; // часы
  timeinfo.tm_min = 30;  // минуты
  timeinfo.tm_sec = 0;   // секунды

  // преобразуем структуру tm в значение time_t
  time_t time = mktime(&timeinfo);
  return time;
}

int main() {

  dbo::Session session;
  std::unique_ptr<dbo::backend::Postgres> pg{new dbo::backend::Postgres(
      "host=localhost port=5432 dbname=for_project_ARKITAIL user=antiho "
      "password=qwerty")};
  session.setConnection(std::move(pg));
  dbo::Transaction transaction{session};

  session.mapClass<calendars>("calendars");

  session.mapClass<events>("events");
  session.mapClass<tags>("tags");
  session.mapClass<nodes>("nodes");
  session.mapClass<directory>("directory");
  session.mapClass<users>("users");
  session.createTables(); // already create

  // Получаем список пользователей из базы данных
  typedef dbo::collection<dbo::ptr<users>> Users;
  Users userss = session.find<users>();

  // Получаем список ивентов из базы данных
  typedef dbo::collection<dbo::ptr<events>> Events;
  Events eventss = session.find<events>();

  // Получаем список ивентов из базы данных
  typedef dbo::collection<dbo::ptr<calendars>> Calendars;
  Calendars calendarss = session.find<calendars>();

  // std::unique_ptr<users> user{new users()};
  // user->login = "Joeb";
  // user->email = "email@gmail.com";
  // user->password = "Secret";
  // user->avatar = read_file("avatar2.jpg");
  // dbo::ptr<users> userPtr = session.add(std::move(user));

  // std::unique_ptr<calendars> calendar{new calendars()};
  // calendar->name = "calendar2";
  // calendar->visibility = true;
  // dbo::ptr<calendars> calendarPtr = session.add(std::move(calendar));

  // std::unique_ptr<events> event{new events()};
  // event->name = "event2";
  // event->time_start = set_time_start();
  // event->time_end = set_time_end();
  // event->description = "random description";
  // calendarPtr = session.find<calendars>().where("name =
  // ?").bind("calendar1"); event->calendar = calendarPtr; dbo::ptr<events>
  // eventPtr = session.add(std::move(event));

  // std::cout << "We have " << userss.size() << " users:" << std::endl;

  // // Печатаем список пользователей
  // for (const dbo::ptr<users> &user : userss) {
  //     std::cout << user->login << ", " << user->email << ", " <<
  //     user->password << std::endl;
  // }

  // std::cout << "We have " << eventss.size() << " events:" << std::endl;

  // // Печатаем список событий
  // for (const dbo::ptr<events> &event : eventss) {
  //     std::cout << event->name << ", " << event->time_start << ", " <<
  //     event->time_end << ", " << event->description << std::endl;
  // }
  transaction.commit();
  return 0;
}
