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
        std::chrono::time_point<std::chrono::steady_clock> begin_point,
        std::chrono::time_point<std::chrono::steady_clock> end_point
    );

    int id;
    int calendar_id;
    std::string name;
    std::string description;
    std::chrono::time_point<std::chrono::steady_clock> begin_point;
    std::chrono::time_point<std::chrono::steady_clock> end_point;

};
