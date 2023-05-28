#include "time_utils.hpp"

#include <Wt/WString.h>

Wt::WString createTime(size_t hour) {
    return Wt::WString(hour < 10 ? "0{1}:00" : "{1}:00").arg(hour);
}
