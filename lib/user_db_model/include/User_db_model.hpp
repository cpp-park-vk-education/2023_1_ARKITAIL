#pragma once

#include "base_for_all.hpp"
#include <vector>
#include <fstream>

std::vector<unsigned char> read_file(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    return std::vector<unsigned char>(
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>()
    );
}

class users {
public:
    std::string login;
    std::string email;
    std::string password;
    std::vector<unsigned char> avatar;
    dbo::ptr<calendars> calendar;


    template<class Action>
    void persist(Action& a) {
        dbo::field(a, login, "login");
        dbo::field(a, email, "email");
        dbo::field(a, password, "password");
        dbo::field(a, avatar, "avatar");
        dbo::belongsTo(a, calendar, "calendar");
    }
};