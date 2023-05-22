#pragma once

#include <memory>

class OptionsW;

class OptionsWBuilderBase {
  public:
    OptionsWBuilderBase* createOptionsW();

    virtual OptionsWBuilderBase* addOptionRemove();
    virtual OptionsWBuilderBase* addOptionEdit();
    virtual OptionsWBuilderBase* addOptionAddCalendar();
    virtual OptionsWBuilderBase* addOptionAddDirectory();
    virtual OptionsWBuilderBase* addOptionSubscribe();
    virtual OptionsWBuilderBase* addOptionUnsubscribe();

    std::unique_ptr<OptionsW> getOptionsW();

  protected:
    std::unique_ptr<OptionsW> options_w;
};
