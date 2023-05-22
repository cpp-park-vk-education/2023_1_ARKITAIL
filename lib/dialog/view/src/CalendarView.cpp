#include "CalendarView.hpp"

#include <memory>

#include <Wt/WColorPicker.h>
#include <Wt/WComboBox.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>
#include <Wt/WTextArea.h>

#include "CalendarModel.hpp"
#include "SessionScopeMap.hpp"

namespace dialog {
CalendarView::CalendarView(std::shared_ptr<CalendarModel> model)
    : model_(model) {
  setTemplateText(Wt::WString::tr("calendar-settings"));

  addFunction("id", &WTemplate::Functions::id);

  InitializeSummary();
  InitializeDescription();
  InitializeVisibility();
  InitializeColor();
  InitializeButton();

  updateView(model_.get());
}

void CalendarView::InitializeSummary() {
  auto summary = std::make_unique<Wt::WLineEdit>();
  summary_ = summary.get();
  setFormWidget(CalendarModel::kSummary, std::move(summary));
}

void CalendarView::InitializeDescription() {
  auto description = std::make_unique<Wt::WTextArea>();
  description_ = description.get();
  setFormWidget(CalendarModel::kDescription, std::move(description));
}

void CalendarView::InitializeVisibility() {
  auto visibility = std::make_unique<Wt::WComboBox>();
  visibility->addItem("Публичный");
  visibility->addItem("Приватный");
  visibility_ = visibility.get();
  setFormWidget(CalendarModel::kVisibility, std::move(visibility));
}

void CalendarView::InitializeColor() {
  auto color = std::make_unique<Wt::WColorPicker>();
  color_ = color.get();
  setFormWidget(CalendarModel::kColor, std::move(color));
}

void CalendarView::InitializeButton() {
}

void CalendarView::HandleInput() {
}
} // namespace dialog
