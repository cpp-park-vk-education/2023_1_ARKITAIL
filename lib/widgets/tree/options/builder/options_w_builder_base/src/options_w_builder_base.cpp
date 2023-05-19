#include "options_w_builder_base.hpp"

#include <memory>

#include "options_w.hpp"

OptionsWBuilderBase* OptionsWBuilderBase::createOptionsW() {
    options_w = std::make_unique<OptionsW>();
    return this;
}

OptionsWBuilderBase* OptionsWBuilderBase::addOptionRemove() {
    return this;
}

OptionsWBuilderBase* OptionsWBuilderBase::addOptionEdit() {
    return this;
}

OptionsWBuilderBase* OptionsWBuilderBase::addOptionAddCalendar() {
    return this;
}

OptionsWBuilderBase* OptionsWBuilderBase::addOptionAddDirectory() {
    return this;
}

OptionsWBuilderBase* OptionsWBuilderBase::addOptionSubscribe() {
    return this;
}

OptionsWBuilderBase* OptionsWBuilderBase::addOptionUnsubscribe() {
    return this;
}

std::unique_ptr<OptionsW> OptionsWBuilderBase::getOptionsW() {
    return std::move(options_w);
}
