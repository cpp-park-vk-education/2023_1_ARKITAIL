#pragma once

#include <memory>

#include <Wt/WTemplateFormView.h>
#include <Wt/WColorPicker.h>
#include <Wt/WComboBox.h>
#include <Wt/WLineEdit.h>
#include <Wt/WTextArea.h>

#include "calendar.hpp"
#include "calendar_settings_fm.hpp"

class CalendarSettingsFV : public Wt::WTemplateFormView {
 public:
  CalendarSettingsFV();

  void HandleInput();
  void UpdateModel(std::unique_ptr<Calendar> calendar);
 private:
  std::shared_ptr<CalendarSettingsFM> model_;
  
  Wt::WLineEdit* title_;
  Wt::WTextArea* description_;
  Wt::WComboBox* visibility_;
  Wt::WColorPicker* color_;
};
