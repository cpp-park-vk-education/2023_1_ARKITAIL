#include "options_personal_calendar_w.hpp"

OptionsPersonalCalendarW::OptionsPersonalCalendarW() {
    addItem("Удалить")->triggered().connect([=] { select_option_.emit(REMOVE); });
}