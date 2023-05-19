#pragma once

#include <memory>

#include "options_w_builder_base.hpp"
class OptionsW;

class OptionsWDirector {
  public:
    OptionsWDirector();

    std::unique_ptr<OptionsW> createOptionsProfileW(OptionsWBuilderBase& builder);
    std::unique_ptr<OptionsW> createOptionsCalendarsDirW(OptionsWBuilderBase& builder);
    std::unique_ptr<OptionsW> createOptionsPersonalCalendarW(OptionsWBuilderBase& builder);
    std::unique_ptr<OptionsW> createOptionsSubscriptionW(OptionsWBuilderBase& builder);
    std::unique_ptr<OptionsW> createOptionsUnsubscriptionW(OptionsWBuilderBase& builder);
};
