#include "options_dir_w.hpp"

OptionsDirW::OptionsDirW() {
    addItem("Добавить календарь")->triggered().connect([=] { select_option_.emit(ADD_CALENDAR); });
    addItem("Добавить директорию")->triggered().connect([=] { select_option_.emit(ADD_DIR); });
}