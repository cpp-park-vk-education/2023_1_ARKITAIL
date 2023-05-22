#include "options_w_director.hpp"

#include <memory>

#include "options_w.hpp"
#include "options_w_builder_base.hpp"

OptionsWDirector::OptionsWDirector() {}

std::unique_ptr<OptionsW> OptionsWDirector::createOptionsProfileW(OptionsWBuilderBase& builder) {
    return std::move(builder.createOptionsW()->addOptionRemove()->getOptionsW());
}

std::unique_ptr<OptionsW> OptionsWDirector::createOptionsCalendarsDirW(
    OptionsWBuilderBase& builder) {
    return std::move(builder.createOptionsW()
                         ->addOptionEdit()
                         ->addOptionAddCalendar()
                         ->addOptionAddDirectory()
                         ->addOptionRemove()
                         ->getOptionsW());
}

std::unique_ptr<OptionsW> OptionsWDirector::createOptionsPersonalCalendarW(
    OptionsWBuilderBase& builder) {
    return std::move(builder.createOptionsW()->addOptionEdit()->addOptionRemove()->getOptionsW());
}

std::unique_ptr<OptionsW> OptionsWDirector::createOptionsSubscriptionW(
    OptionsWBuilderBase& builder) {
    return std::move(builder.createOptionsW()->addOptionSubscribe()->getOptionsW());
}

std::unique_ptr<OptionsW> OptionsWDirector::createOptionsUnsubscriptionW(
    OptionsWBuilderBase& builder) {
    return std::move(builder.createOptionsW()->addOptionUnsubscribe()->getOptionsW());
}
