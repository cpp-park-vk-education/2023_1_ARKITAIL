#pragma once

#include <memory>

#include <Wt/WTemplateFormView.h>

#include "Calendar.hpp"
#include "CalendarModel.hpp"

namespace dialog {
class CalendarView : public Wt::WTemplateFormView {
 public:
  explicit CalendarView(CalendarSptr calendar = nullptr);

  std::shared_ptr<CalendarModel> model() const;
 private:
  void InitializeSummary();
  void InitializeDescription();
  void InitializeVisibility();
  void InitializeColor();
  
  std::shared_ptr<CalendarModel> model_;
};
} // namespace dialog
