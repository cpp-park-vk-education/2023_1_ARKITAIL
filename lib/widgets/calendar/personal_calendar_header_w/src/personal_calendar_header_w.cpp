#include "personal_calendar_header_w.hpp"

#include <Wt/WDate.h>
#include <Wt/WLogger.h>
#include <Wt/WPushButton.h>

#include "CreateEventDialog.hpp"

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
    dialog::CreateEventDialog* dialog = addChild(std::make_unique<dialog::CreateEventDialog>());

    dialog->show();

    dialog->finished().connect([=]() {
        change_selected_date_.emit(selected_date_);
        removeChild(dialog);
        Wt::log("CreateEventDialog removed");
    });
}
