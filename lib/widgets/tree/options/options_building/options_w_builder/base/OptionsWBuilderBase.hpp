#pragma once

#include <memory>

#include "OptionsW.hpp"

class OptionsWBuilderBase {
  public:
    OptionsWBuilderBase();
    ~OptionsWBuilderBase() = default;
    OptionsWBuilderBase* createOptionsW();

    virtual OptionsWBuilderBase* addOptionRemove();
    virtual OptionsWBuilderBase* addOptionEdit();
    virtual OptionsWBuilderBase* addOptionAddCalendar();
    virtual OptionsWBuilderBase* addOptionAddDirectory();
    virtual OptionsWBuilderBase* addOptionSubscribe();
    virtual OptionsWBuilderBase* addOptionUnsubscribe();

    std::unique_ptr<OptionsW> getOptionsW();

  protected:
    size_t options_count_;
    std::unique_ptr<OptionsW> options_w_;
};
