#include "options_calendars_dir_w.hpp"

#include "options_dir_w.hpp"

OptionsCalendarsDirW::OptionsCalendarsDirW() {
    addItem("Удалить")->triggered().connect([=] { select_option_.emit(REMOVE); });
    addItem("Редактировать")->triggered().connect([=] { select_option_.emit(EDIT); });
}