#include "CalendarView.hpp"

#include <memory>

#include <Wt/WColorPicker.h>
#include <Wt/WComboBox.h>
#include <Wt/WLineEdit.h>
#include <Wt/WTemplateFormView.h>
#include <Wt/WTextArea.h>

#include "CalendarModel.hpp"

namespace dialog {
std::shared_ptr<CalendarModel> CalendarView::model() const {
  return model_;
}

// по умолчанию calendar = nullptr
CalendarView::CalendarView(CalendarSptr calendar)
    : Wt::WTemplateFormView(Wt::WString::tr("calendar")),
      model_(std::make_shared<CalendarModel>(calendar)) {
  InitializeSummary();
  InitializeDescription();
  InitializeVisibility();
  InitializeColor();

  bindEmpty("validation-status");

  updateView(model_.get());
}

void CalendarView::InitializeSummary() {
  setFormWidget(CalendarModel::kSummary, std::make_unique<Wt::WLineEdit>());
}

void CalendarView::InitializeDescription() {
  setFormWidget(CalendarModel::kDescription, std::make_unique<Wt::WTextArea>());
}

void CalendarView::InitializeVisibility() {
  auto visibility = std::make_unique<Wt::WComboBox>();
  visibility->addItem("Публичный");
  visibility->addItem("Приватный");
  setFormWidget(CalendarModel::kVisibility, std::move(visibility));
}

void CalendarView::InitializeColor() {
  setFormWidget(CalendarModel::kColor, std::make_unique<Wt::WColorPicker>());
}
} // namespace dialog
