#pragma once

#include <Wt/WPushButton.h>
#include <memory>

#include <Wt/WTemplateFormView.h>
#include <Wt/WColorPicker.h>
#include <Wt/WComboBox.h>
#include <Wt/WLineEdit.h>
#include <Wt/WTextArea.h>

#include "calendar_settings_model.hpp"

class CalendarSettingsView : public Wt::WTemplateFormView {
 public:
  CalendarSettingsView(std::unique_ptr<Calendar>&& calendar = nullptr);

  void HandleInput();

  Wt::Signal<std::shared_ptr<Calendar>>& calendar_created();
 private:
  std::shared_ptr<CalendarSettingsModel> model_;
  
  Wt::WLineEdit* title_;
  Wt::WTextArea* description_;
  Wt::WComboBox* visibility_;
  Wt::WColorPicker* color_;
  Wt::WPushButton* button_;

  Wt::Signal<std::shared_ptr<Calendar>> calendar_created_;
};
