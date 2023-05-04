#pragma once

#include <chrono>
#include <string>

class EventManager {
public:
    static std::chrono::time_point<std::chrono::steady_clock> parseTime(std::string raw_tp);

};

