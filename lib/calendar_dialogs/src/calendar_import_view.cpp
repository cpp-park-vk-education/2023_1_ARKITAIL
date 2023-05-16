#include "calendar_import_view.hpp"

#include <memory>

#include <Wt/WFileUpload.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>
#include <Wt/WTemplateFormView.h>

#include "calendar_import_model.hpp"

CalendarImportView::CalendarImportView() {
  model_ = std::make_shared<CalendarImportModel>();

  setTemplateText(Wt::WString::tr("calendar-import"));

  addFunction("id", &Wt::WTemplate::Functions::id);

  auto import_iCalendar = std::make_unique<Wt::WFileUpload>();
  import_iCalendar_ = import_iCalendar.get();
  setFormWidget(
      CalendarImportModel::kImportiCalendarField, std::move(import_iCalendar));

  auto button = bindWidget(
      "submit-button", std::make_unique<Wt::WPushButton>("OK"));
  bindString("submit-info", Wt::WString());
  button->addStyleClass("btn btn-success");
  button->clicked().connect(this, &CalendarImportView::HandleInput);
  
  updateView(model_.get());
}

void CalendarImportView::HandleInput() {
  updateModel(model_.get());

  if (model_->validate()) {
    // Раскомментировать при слиянии:
    // calendar_manager.add(model_->GetData());
    calendar_created_.emit(model_->GetData());
  } else {
    bindEmpty("submit-info");
  }

  updateView(model_.get());
}

Wt::Signal<std::shared_ptr<Calendar>>& CalendarImportView::calendar_created() {
  return calendar_created_;
}
