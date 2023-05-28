#pragma once

#include <memory>

#include "OptionsWBuilder.hpp"
class OptionsW;

class OptionsWDirector {
  public:
    OptionsWDirector();

    std::unique_ptr<OptionsW> createOptionsProfileW(OptionsWBuilder& builder);
    std::unique_ptr<OptionsW> createOptionsCalendarsDirW(OptionsWBuilder& builder);
    std::unique_ptr<OptionsW> createOptionsGroupW(OptionsWBuilder& builder);
    std::unique_ptr<OptionsW> createOptionsPersonalCalendarW(OptionsWBuilder& builder);
    std::unique_ptr<OptionsW> createOptionsSubscriptionW(OptionsWBuilder& builder);
    std::unique_ptr<OptionsW> createOptionsUnsubscriptionW(OptionsWBuilder& builder);
};
