#include "EditCalendarView.hpp"

#include "Calendar.hpp"
#include "CalendarView.hpp"
#include "EditCalendarModel.hpp"
#include "IManagers.hpp"

#include "EditEventModel.hpp"
#include "SessionScopeMap.hpp"

namespace dialog {
EditCalendarView::EditCalendarView(CalendarSptr event)
    : CalendarView(std::make_shared<EditCalendarModel>(event)) {
}

Wt::Signal<CalendarSptr>& EditCalendarView::calendar_updated() {
  return calendar_updated_;
}

void EditCalendarView::InitializeButton() {
  button_ = bindWidget(
      "submit-button",
      std::make_unique<Wt::WPushButton>("Сохранить"));
  bindString("submit-info", std::string());
  button_->addStyleClass("btn btn-success");
  button_->clicked().connect(this, &EditCalendarView::HandleInput);
}

void EditCalendarView::HandleInput() {
  updateModel(model_.get());

  if (model_->validate()) {
    model_->UpdateCalendar();

    IManagers* managers = SessionScopeMap::instance().get()->managers();
    managers->calendar_manager()->update(model_->calendar());
    calendar_updated_.emit(model_->calendar());

    bindString("submit-info", Wt::WString("Календарь успешно изменён!"));
  } else {
    bindEmpty("submit-info");
  }

  updateView(model_.get());
}
} // namespace dialog
