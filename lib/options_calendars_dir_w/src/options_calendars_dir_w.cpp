#include "options_calendars_dir_w.hpp"

OptionsCalendarsDirW::OptionsCalendarsDirW() {
    addItem("Добавить календарь")->triggered().connect([=] { select_option_.emit(ADD_CALENDAR); });
    addItem("Добавить директорию")->triggered().connect([=] { select_option_.emit(ADD_DIR); });
    addItem("Удалить")->triggered().connect([=] { select_option_.emit(REMOVE); });
}