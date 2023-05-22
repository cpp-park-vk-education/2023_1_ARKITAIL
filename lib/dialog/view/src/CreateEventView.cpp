#include "CreateEventView.hpp"

#include "IManagers.hpp"
#include "SessionScopeMap.hpp"
#include "CreateEventModel.hpp"

namespace dialog {
CreateEventView::CreateEventView()
    : EventView(std::make_shared<CreateEventModel>()) {
}

Wt::Signal<EventSptr>& CreateEventView::event_created() {
  return event_created_;
}

void CreateEventView::InitializeButton() {
  button_ = bindWidget(
      "submit-button",
      std::make_unique<Wt::WPushButton>("Создать"));
  bindString("submit-info", std::string());
  button_->addStyleClass("btn btn-success");
  button_->clicked().connect(this, &CreateEventView::HandleInput);
}

void CreateEventView::HandleInput() {
  updateModel(model_.get());

  if (model_->validate()) {
    // заносим актуальные поля формы в calendar
    model_->UpdateEvent();

    IManagers* managers = SessionScopeMap::instance().get()->managers();
    // добавляем calendar в БД и получаем его id
    size_t calendar_id = managers->event_manager()->add(model_->event());
    // получаем этот же calendar с установленными id, node_id, owner_id
    model_->set_event(managers->event_manager()->get(calendar_id));
    // выпускаем валидный calendar
    event_created_.emit(model_->event());

    bindString("submit-info", Wt::WString("Календарь успешно создан"));
    model_.get()->reset();
    model_->set_event(nullptr);
  } else {
    bindEmpty("submit-info");
  }

  updateView(model_.get());
}
} // namespace dialog
