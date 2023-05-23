#include "CreateCalendarView.hpp"

#include "CreateCalendarModel.hpp"

namespace dialog {
CreateCalendarView::CreateCalendarView()
    : CalendarView(std::make_shared<CreateCalendarModel>()) {
}
} // namespace dialog
