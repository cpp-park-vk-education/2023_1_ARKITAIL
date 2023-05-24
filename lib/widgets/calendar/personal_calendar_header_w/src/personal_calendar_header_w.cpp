#include "personal_calendar_header_w.hpp"

#include <Wt/WPushButton.h>

PersonalCalendarHeaderW::PersonalCalendarHeaderW() :
    CalendarHeaderW() {
    button_add_event_ = container_option_range_->addNew<Wt::WPushButton>("Добавить событие");
    button_add_event_->addStyleClass("col mx-3");
}

void PersonalCalendarHeaderW::addConnections() {
    button_add_event_->clicked().connect([=] {
        // ...
    });
}

void PersonalCalendarHeaderW::addEvent() {
    change_selected_date_.emit(selected_date_);
    // added_event_.emit(); // если по сигналу будет передаваться событие
}
