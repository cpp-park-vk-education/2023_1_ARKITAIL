#pragma once

#include <memory>

#include "OptionsWBuilderBase.hpp"

class OptionsW;

class OptionsWBuilder : public OptionsWBuilderBase {
  public:
    OptionsWBuilder();
    ~OptionsWBuilder() = default;

    OptionsWBuilder* addOptionRemove() override;
    OptionsWBuilder* addOptionEdit() override;
    OptionsWBuilder* addOptionAddCalendar() override;
    OptionsWBuilder* addOptionAddDirectory() override;
    OptionsWBuilder* addOptionSubscribe() override;
    OptionsWBuilder* addOptionUnsubscribe() override;
};
