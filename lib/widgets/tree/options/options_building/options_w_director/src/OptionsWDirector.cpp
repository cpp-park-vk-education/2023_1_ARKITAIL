#include "OptionsWDirector.hpp"

#include <memory>

#include "OptionsW.hpp"
#include "OptionsWBuilder.hpp"

OptionsWDirector::OptionsWDirector() {}

std::unique_ptr<OptionsW> OptionsWDirector::createOptionsProfileW(OptionsWBuilder& builder) {
    return builder.createOptionsW()
        ->addOptionRemove()
        ->getOptionsW();
}

std::unique_ptr<OptionsW> OptionsWDirector::createOptionsGroupW(OptionsWBuilder& builder) {
    return builder.createOptionsW()
        ->addOptionAddCalendar()
        ->addOptionAddDirectory()
        ->getOptionsW();
}

std::unique_ptr<OptionsW> OptionsWDirector::createOptionsCalendarsDirW(OptionsWBuilder& builder) {
    return builder.createOptionsW()
        ->addOptionEdit()
        ->addOptionAddCalendar()
        ->addOptionAddDirectory()
        ->addOptionRemove()
        ->getOptionsW();
}

std::unique_ptr<OptionsW> OptionsWDirector::createOptionsPersonalCalendarW(
    OptionsWBuilder& builder) {
    return builder.createOptionsW()
        ->addOptionEdit()
        ->addOptionRemove()
        ->getOptionsW();
}

std::unique_ptr<OptionsW> OptionsWDirector::createOptionsSubscriptionW(OptionsWBuilder& builder) {
    return builder.createOptionsW()
        ->addOptionSubscribe()
        ->getOptionsW();
}

std::unique_ptr<OptionsW> OptionsWDirector::createOptionsUnsubscriptionW(OptionsWBuilder& builder) {
    return builder.createOptionsW()
        ->addOptionUnsubscribe()
        ->getOptionsW();
}
