#include "options_w_director.hpp"

#include <memory>

#include "options_w.hpp"
#include "options_w_builder.hpp"

OptionsWDirector::OptionsWDirector() {}

std::unique_ptr<OptionsW> OptionsWDirector::createOptionsProfileW(OptionsWBuilder& builder) {
    return std::move(builder.createOptionsW()->addOptionRemove()->getOptionsW());
}

std::unique_ptr<OptionsW> createOptionsGroupW(OptionsWBuilder& builder) {
    return std::move(
        builder.createOptionsW()->addOptionAddCalendar()->addOptionAddDirectory()->getOptionsW());
}

std::unique_ptr<OptionsW> OptionsWDirector::createOptionsCalendarsDirW(OptionsWBuilder& builder) {
    return std::move(builder.createOptionsW()
                         ->addOptionEdit()
                         ->addOptionAddCalendar()
                         ->addOptionAddDirectory()
                         ->addOptionRemove()
                         ->getOptionsW());
}

std::unique_ptr<OptionsW> OptionsWDirector::createOptionsPersonalCalendarW(
    OptionsWBuilder& builder) {
    return std::move(builder.createOptionsW()->addOptionEdit()->addOptionRemove()->getOptionsW());
}

std::unique_ptr<OptionsW> OptionsWDirector::createOptionsSubscriptionW(OptionsWBuilder& builder) {
    return std::move(builder.createOptionsW()->addOptionSubscribe()->getOptionsW());
}

std::unique_ptr<OptionsW> OptionsWDirector::createOptionsUnsubscriptionW(OptionsWBuilder& builder) {
    return std::move(builder.createOptionsW()->addOptionUnsubscribe()->getOptionsW());
}
