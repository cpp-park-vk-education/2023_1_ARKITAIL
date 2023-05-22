#pragma once

#include <cstddef>
#include <string>

class User {
public:
    User();
    User(int id, int root_id, std::string login, std::string email, std::string nickname, std::string description);

    int id;
    int root_id;

    std::string login;
    std::string email;

    std::string nickname;
    std::string description;

};
