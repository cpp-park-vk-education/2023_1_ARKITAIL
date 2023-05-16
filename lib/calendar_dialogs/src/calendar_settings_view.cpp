#include "calendar_settings_view.hpp"

#include <Wt/WColorPicker.h>
#include <Wt/WComboBox.h>
#include <memory>

#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>
#include <Wt/WTextArea.h>

#include "calendar_settings_model.hpp"

// по умолчаню calendar = nullptr
CalendarSettingsView::CalendarSettingsView(
    std::unique_ptr<Calendar>&& calendar) {
  model_ = std::make_shared<CalendarSettingsModel>(std::move(calendar));

  setTemplateText(Wt::WString::tr("calendar-settings"));

  addFunction("id", &WTemplate::Functions::id);

  auto title = std::make_unique<Wt::WLineEdit>();
  title_ = title.get();
  setFormWidget(CalendarSettingsModel::kTitleField, std::move(title));

  auto description = std::make_unique<Wt::WTextArea>();
  description_ = description.get();
  setFormWidget(CalendarSettingsModel::kDescriptionField, std::move(description));

  auto visibility = std::make_unique<Wt::WComboBox>();
  visibility->addItem("Публичный");
  visibility->addItem("Приватный");
  visibility_ = visibility.get();
  setFormWidget(CalendarSettingsModel::kVisibilityField, std::move(visibility));

  auto color = std::make_unique<Wt::WColorPicker>();
  color_ = color.get();
  setFormWidget(CalendarSettingsModel::kColorField, std::move(color));

  button_ = bindWidget(
      "submit-button", std::make_unique<Wt::WPushButton>("OK"));
  bindString("submit-info", Wt::WString());
  button_->addStyleClass("btn btn-success");
  button_->clicked().connect(this, &CalendarSettingsView::HandleInput);

  updateView(model_.get());
}

void CalendarSettingsView::HandleInput() {
  updateModel(model_.get());

  if (model_->validate()) {
    // Раскомментировать при слиянии:
    // calendar_manager.add(model_->GetData());
    calendar_created_.emit(model_->GetData());
    bindString("submit-info", Wt::WString("Успешно!"));
  } else {
    bindEmpty("submit-info");
  }

  updateView(model_.get());
}

Wt::Signal<std::shared_ptr<Calendar>>& CalendarSettingsView::calendar_created() {
  return calendar_created_;
}
