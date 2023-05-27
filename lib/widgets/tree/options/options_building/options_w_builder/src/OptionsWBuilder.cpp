#include "OptionsWBuilder.hpp"

#include <memory>

#include "OptionsW.hpp"

OptionsWBuilder::OptionsWBuilder() {}

OptionsWBuilder* OptionsWBuilder::addOptionRemove() {
    options_w_->addItem("Удалить");
    options_w_->addSignal(options_count_, Action::REMOVE);
    options_count_++;
    return this;
}

OptionsWBuilder* OptionsWBuilder::addOptionEdit() {
    options_w_->addItem("Редактировать");
    options_w_->addSignal(options_count_, Action::EDIT);
    options_count_++;
    return this;
}

OptionsWBuilder* OptionsWBuilder::addOptionAddCalendar() {
    options_w_->addItem("Добавить календарь");
    options_w_->addSignal(options_count_, Action::ADD_CALENDAR);
    options_count_++;
    return this;
}

OptionsWBuilder* OptionsWBuilder::addOptionAddDirectory() {
    options_w_->addItem("Добавить директорию");
    options_w_->addSignal(options_count_, Action::ADD_DIRECTORY);
    options_count_++;
    return this;
}

OptionsWBuilder* OptionsWBuilder::addOptionSubscribe() {
    options_w_->addItem("Подписаться");
    options_w_->addSignal(options_count_, Action::SUBSCRIBE);
    options_count_++;
    return this;
}

OptionsWBuilder* OptionsWBuilder::addOptionUnsubscribe() {
    options_w_->addItem("Отписаться");
    options_w_->addSignal(options_count_, Action::UNSUBSCRIBE);
    options_count_++;
    return this;
}
