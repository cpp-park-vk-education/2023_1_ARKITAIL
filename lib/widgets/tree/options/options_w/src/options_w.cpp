#include "options_w.hpp"

OptionsW::OptionsW() {}

Wt::Signal<Action>& OptionsW::selectedOption() {
    return select_option_;
}

OptionsW* OptionsW::addOptionRemove() {
    addItem("Удалить")->triggered().connect([=] {
        select_option_.emit(Action::REMOVE);
    });
}

OptionsW* OptionsW::addOptionEdit() {
    addItem("Редактировать")->triggered().connect([=] {
        select_option_.emit(Action::EDIT);
    });
}

OptionsW* OptionsW::addOptionAddCalendar() {
    addItem("Добавить календарь")->triggered().connect([=] {
        select_option_.emit(Action::ADD_CALENDAR);
    });
}

OptionsW* OptionsW::addOptionAddDirectory() {
    addItem("Добавить директорию")->triggered().connect([=] {
        select_option_.emit(Action::ADD_DIRECTORY);
    });
}

OptionsW* OptionsW::addOptionSubscribe() {
    addItem("Подписаться")->triggered().connect([=] {
        select_option_.emit(Action::UNSUBSCRIBE);
    });
}

OptionsW* OptionsW::addOptionUnsubscribe() {
    addItem("Отписаться")->triggered().connect([=] {
        select_option_.emit(Action::UNSUBSCRIBE);
    });
}
