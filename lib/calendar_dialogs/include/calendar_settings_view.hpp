#pragma once

#include <memory>

#include <Wt/WTemplateFormView.h>
#include <Wt/WColorPicker.h>
#include <Wt/WComboBox.h>
#include <Wt/WLineEdit.h>
#include <Wt/WTextArea.h>

#include "calendar_settings_model.hpp"

class CalendarSettingsView : public Wt::WTemplateFormView {
 public:
  CalendarSettingsView();

  void HandleInput();
 private:
  std::shared_ptr<CalendarSettingsModel> model_;
  
  Wt::WLineEdit* title_;
  Wt::WTextArea* description_;
  Wt::WComboBox* visibility_;
  Wt::WColorPicker* color_;
};
