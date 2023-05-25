#pragma once

#include <memory>

#include <Wt/WPushButton.h>
#include <Wt/WTemplateFormView.h>

#include "CalendarModel.hpp"

namespace dialog {
class CalendarView : public Wt::WTemplateFormView {
 public:
  std::shared_ptr<CalendarModel> model() const;

 protected:
  CalendarView(std::shared_ptr<CalendarModel> model);

  void InitializeSummary();
  void InitializeDescription();
  void InitializeVisibility();
  void InitializeColor();
  
  std::shared_ptr<CalendarModel> model_;
};
} // namespace dialog
