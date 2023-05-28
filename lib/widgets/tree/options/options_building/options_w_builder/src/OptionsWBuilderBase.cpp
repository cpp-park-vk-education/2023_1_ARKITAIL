#include "OptionsWBuilderBase.hpp"

#include <memory>

#include "OptionsW.hpp"

OptionsWBuilderBase::OptionsWBuilderBase() {}

OptionsWBuilderBase* OptionsWBuilderBase::createOptionsW() {
    options_count_ = 0;
    options_w_ = std::make_unique<OptionsW>();
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
    auto tmp = std::make_unique<OptionsW>();
    tmp.swap(options_w_);
    return tmp;
}
