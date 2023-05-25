#include "personal_calendar_header_w.hpp"

#include <Wt/WDate.h>
#include <Wt/WLogger.h>
#include <Wt/WPushButton.h>
#include "CreateEventDialog.hpp"

PersonalCalendarHeaderW::PersonalCalendarHeaderW() :
    CalendarHeaderW() {
    button_add_event_ 
        = container_option_range_->addNew<Wt::WPushButton>("Добавить событие");
    // (affeeal): пока непонятно, где назначать обработчик button_add_event_,
    // поэтому прикреплю его здесь
    button_add_event_->clicked().connect(
        this, &PersonalCalendarHeaderW::handleAddEvent);
    button_add_event_->addStyleClass("col mx-3");
}

void PersonalCalendarHeaderW::addConnections() {
  // ...
}

void PersonalCalendarHeaderW::addEvent() {
    change_selected_date_.emit(selected_date_);
    // added_event_.emit(); // если по сигналу будет передаваться событие
}

void PersonalCalendarHeaderW::handleAddEvent() {
    dialog::CreateEventDialog* dialog = addChild(
        std::make_unique<dialog::CreateEventDialog>());

    dialog->show();

    // dialog->event_created().connect(...);
    
    dialog->finished().connect([=] {
        removeChild(dialog);
        Wt::log("CreateEventDialog removed");
    });
}
