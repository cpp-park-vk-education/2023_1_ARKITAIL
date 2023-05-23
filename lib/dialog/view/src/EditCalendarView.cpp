#include "EditCalendarView.hpp"

#include "EditCalendarModel.hpp"

namespace dialog {
EditCalendarView::EditCalendarView(CalendarSptr event)
    : CalendarView(std::make_shared<EditCalendarModel>(event)) {
}
} // namespace dialog
