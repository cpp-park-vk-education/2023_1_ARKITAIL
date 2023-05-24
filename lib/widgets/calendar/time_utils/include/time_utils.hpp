#pragma once
#include <Wt/WString.h>

enum TimeInterval {
    DAYS_IN_WEEK = 7,
    HOURS_PER_DAY = 24,
};

Wt::WString createTime(size_t hour);
