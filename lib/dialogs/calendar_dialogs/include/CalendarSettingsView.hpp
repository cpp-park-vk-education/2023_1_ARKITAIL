#pragma once

#include <memory>

#include <Wt/WColorPicker.h>
#include <Wt/WComboBox.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WTemplateFormView.h>
#include <Wt/WTextArea.h>

#include "CalendarSettingsModel.hpp"

class CalendarSettingsView : public Wt::WTemplateFormView {
 public:
  CalendarSettingsView(std::shared_ptr<Calendar> calendar = nullptr);

  Wt::Signal<std::shared_ptr<Calendar>>& calendar_created();
 private:
  void HandleInput();
  
  std::shared_ptr<CalendarSettingsModel> model_;
  
  Wt::WLineEdit* title_;
  Wt::WTextArea* description_;
  Wt::WComboBox* visibility_;
  Wt::WColorPicker* color_;
  Wt::WPushButton* button_;

  Wt::Signal<std::shared_ptr<Calendar>> calendar_created_;
};
