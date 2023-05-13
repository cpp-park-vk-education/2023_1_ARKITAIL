#pragma once

#include <cstddef>
#include <string>

class User {
public:
    User();

    size_t id;
    size_t root_id;

    std::string login;
    std::string email;

    std::string nickname;
    std::string description;

};
