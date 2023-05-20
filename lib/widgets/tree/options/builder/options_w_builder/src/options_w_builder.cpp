#include "options_w_builder.hpp"

#include <memory>

#include "options_w.hpp"

OptionsWBuilder::OptionsWBuilder() {}

OptionsWBuilder* OptionsWBuilder::addOptionRemove() {
    options_w->addItem("Удалить")->triggered().connect([=] {
        options_w->select_option_.emit(Action::REMOVE);
    });
    return this;
}

OptionsWBuilder* OptionsWBuilder::addOptionEdit() {
    options_w->addItem("Редактировать")->triggered().connect([=] {
        options_w->select_option_.emit(Action::EDIT);
    });
    return this;
}

OptionsWBuilder* OptionsWBuilder::addOptionAddCalendar() {
    options_w->addItem("Добавить календарь")->triggered().connect([=] {
        options_w->select_option_.emit(Action::ADD_CALENDAR);
    });
    return this;
}

OptionsWBuilder* OptionsWBuilder::addOptionAddDirectory() {
    options_w->addItem("Добавить директорию")->triggered().connect([=] {
        options_w->select_option_.emit(Action::ADD_DIRECTORY);
    });
    return this;
}

OptionsWBuilder* OptionsWBuilder::addOptionSubscribe() {
    options_w->addItem("Подписаться")->triggered().connect([=] {
        options_w->select_option_.emit(Action::UNSUBSCRIBE);
    });
    return this;
}

OptionsWBuilder* OptionsWBuilder::addOptionUnsubscribe() {
    options_w->addItem("Отписаться")->triggered().connect([=] {
        options_w->select_option_.emit(Action::UNSUBSCRIBE);
    });
    return this;
}
