#pragma once

#include <memory>

#include <Wt/WTemplateFormView.h>
#include <Wt/WCheckBox.h>
#include <Wt/WComboBox.h>
#include <Wt/WDateEdit.h>
#include <Wt/WLineEdit.h>
#include <Wt/WTextArea.h>
#include <Wt/WTimeEdit.h>
#include <Wt/WSpinBox.h>

#include "event.hpp"
#include "event_settings_fm.hpp"

class EventSettingsFV : public Wt::WTemplateFormView {
 public:
  EventSettingsFV();

  void HandleInput();
  void UpdateModel(std::unique_ptr<Event> event);
 private:
  std::shared_ptr<EventSettingsFM> model_;

  Wt::WLineEdit* title_;
  Wt::WTextArea* description_;
  Wt::WComboBox* calendar_;

  Wt::WTimeEdit* begin_time_;
  Wt::WDateEdit* begin_date_;
  Wt::WTimeEdit* end_time_;
  Wt::WDateEdit* end_date_;
  Wt::WCheckBox* all_day_;

  Wt::WComboBox* repeat_;
  Wt::WDateEdit* until_;
  Wt::WSpinBox* interval_;
};
