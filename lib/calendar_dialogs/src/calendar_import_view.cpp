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
      "submit-button", std::make_unique<Wt::WPushButton>("Импортировать"));
  bindString("submit-info", Wt::WString());
  button->addStyleClass("btn-success");
  button->clicked().connect(this, &CalendarImportView::HandleInput);
  
  updateView(model_.get());
}

void CalendarImportView::HandleInput() {
  updateModel(model_.get());

  if (model_->validate()) {
    // ...
  } else {
    bindEmpty("submit-info");
  }

  updateView(model_.get());
}
