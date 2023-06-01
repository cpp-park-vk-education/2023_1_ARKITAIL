#pragma once

#include <vector>

#include "Calendar.hpp"
#include "ICalendarManager.hpp"
#include "Node.hpp"

class CalendarManagerStub : public ICalendarManager {
  public:
    CalendarManagerStub(std::vector<Calendar> calendars);
    CalendarSptr get(size_t calendar_id) override;

  private:
    std::vector<Calendar> calendars_;

    size_t add(CalendarSptr calendar, size_t directory_id) override {
        return size_t();
    }
    void remove(size_t calendar_id) override {}
    void update(CalendarSptr calendar) override {}

    std::vector<EventSptr> getEvents(size_t calendar_id) override {
        return std::vector<EventSptr>();
    }

    std::vector<EventSptr> getEventsByInterval(size_t calendar_id, Wt::WDateTime begin,
                                               Wt::WDateTime end) override {
        return std::vector<EventSptr>();
    }
};
