#include "CreateCalendarView.hpp"

#include "IManagers.hpp"

#include "Calendar.hpp"
#include "CalendarView.hpp"
#include "CreateCalendarModel.hpp"
#include "SessionScopeMap.hpp"

namespace dialog {
CreateCalendarView::CreateCalendarView()
    : CalendarView(std::make_shared<CreateCalendarModel>()) {
}

Wt::Signal<CalendarSptr>& CreateCalendarView::calendar_created() {
  return calendar_created_;
}

void CreateCalendarView::InitializeButton() {
  button_ = bindWidget(
      "submit-button",
      std::make_unique<Wt::WPushButton>("Создать"));
  bindString("submit-info", std::string());
  button_->addStyleClass("btn btn-success");
  button_->clicked().connect(this, &CreateCalendarView::HandleInput);
}

void CreateCalendarView::HandleInput() {
  updateModel(model_.get());

  if (model_->validate()) {
    // заносим актуальные поля формы в calendar
    model_->UpdateCalendar();

    IManagers* managers = SessionScopeMap::instance().get()->managers();
    // добавляем calendar в БД и получаем его id
    size_t calendar_id = managers->calendar_manager()->add(model_->calendar());
    // получаем этот же calendar с установленными id, node_id, owner_id
    model_->set_calendar(managers->calendar_manager()->get(calendar_id));
    // выпускаем валидный calendar
    calendar_created_.emit(model_->calendar());

    bindString("submit-info", Wt::WString("Календарь успешно создан"));
    model_.get()->reset();
    model_->set_calendar(nullptr);
  } else {
    bindEmpty("submit-info");
  }

  updateView(model_.get());
}
} // namespace dialog
