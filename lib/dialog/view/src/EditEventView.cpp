#include "EditEventView.hpp"

#include "IManagers.hpp"

#include "EditEventModel.hpp"
#include "SessionScopeMap.hpp"

namespace dialog {
EditEventView::EditEventView(EventSptr event)
    : EventView(std::make_shared<EditEventModel>(event)) {
}

Wt::Signal<EventSptr>& EditEventView::event_updated() {
  return event_updated_;
}

void EditEventView::InitializeButton() {
  button_ = bindWidget(
      "submit-button",
      std::make_unique<Wt::WPushButton>("Сохранить"));
  bindString("submit-info", std::string());
  button_->addStyleClass("btn btn-success");
  button_->clicked().connect(this, &EditEventView::HandleInput);
}

void EditEventView::HandleInput() {
  updateModel(model_.get());

  if (model_->validate()) {
    model_->UpdateEvent();

    IManagers* managers = SessionScopeMap::instance().get()->managers();
    managers->event_manager()->update(model_->event());
    event_updated_.emit(model_->event());

    bindString("submit-info", Wt::WString("Календарь успешно изменён!"));
  } else {
    bindEmpty("submit-info");
  }

  updateView(model_.get());
}
} // namespace dialog
