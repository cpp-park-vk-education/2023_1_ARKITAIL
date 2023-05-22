#pragma once

#include <cstddef>
#include <chrono>
#include <string>

class Event {
public:
    Event();
    Event(
        int id,
        int calendar_id,
        std::string name,
        std::string description,
        std::string begin_point,
        std::string end_point
    );

    int id;
    int calendar_id;
    std::string name;
    std::string description;
    std::string begin_point;
    std::string end_point;

};
