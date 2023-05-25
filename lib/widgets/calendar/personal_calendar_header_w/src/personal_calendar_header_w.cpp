#include "personal_calendar_header_w.hpp"

#include <Wt/WPushButton.h>

PersonalCalendarHeaderW::PersonalCalendarHeaderW() :
    CalendarHeaderW() {}

PersonalCalendarHeaderW* PersonalCalendarHeaderW::addButtons() {
    CalendarHeaderW::addButtons();
    button_add_event_ = container_option_range_->addNew<Wt::WPushButton>("Добавить событие");
    button_add_event_->addStyleClass("col mx-3");
    return this;
}

PersonalCalendarHeaderW* PersonalCalendarHeaderW::addConnections() {
    CalendarHeaderW::addConnections();
    button_add_event_->clicked().connect(this, &PersonalCalendarHeaderW::addEvent);
    return this;
}

void PersonalCalendarHeaderW::addEvent() {
    change_selected_date_.emit(selected_date_);
    // added_event_.emit(); // если по сигналу будет передаваться событие
}
