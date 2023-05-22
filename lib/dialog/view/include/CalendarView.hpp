#pragma once

#include <memory>

#include <Wt/WColorPicker.h>
#include <Wt/WComboBox.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WTemplateFormView.h>
#include <Wt/WTextArea.h>

#include "CalendarModel.hpp"

namespace dialog {
class CalendarView : public Wt::WTemplateFormView {
 protected:
  CalendarView() = delete;
  CalendarView(std::shared_ptr<CalendarModel> model);

  void InitializeSummary();
  void InitializeDescription();
  void InitializeVisibility();
  void InitializeColor();
  // обработка нажатия на кнопку сохранения переопределяется в классах
  // CreateCalendarView и EditCalendarView
  virtual void InitializeButton();

  virtual void HandleInput();
  
  std::shared_ptr<CalendarModel> model_;
  
  Wt::WLineEdit* summary_;
  Wt::WTextArea* description_;
  Wt::WComboBox* visibility_;
  Wt::WColorPicker* color_;
  Wt::WPushButton* button_;
};
} // namespace dialog
