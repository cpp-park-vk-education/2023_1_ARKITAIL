#include "EditEventDialog.hpp"

#include <Wt/WObject.h>
#include <Wt/WPushButton.h>

#include "Event.hpp"
#include "EventModel.hpp"
#include "IManagers.hpp"
#include "SessionScopeMap.hpp"

namespace dialog {
EditEventDialog::EditEventDialog(EventSptr event)
    : Wt::WDialog("Событие") {
  setClosable(true);
  setWidth(600);
  setHeight(900);
  setMovable(false);

  view_ = contents()->addNew<EventView>(event);

  Wt::WPushButton* submit = footer()->addNew<Wt::WPushButton>("OK");
  submit->addStyleClass("btn btn-success");
  submit->clicked().connect(this, &EditEventDialog::HandleInput);
}

void EditEventDialog::HandleInput() {
  EventModel* model = view_->model().get();
  view_->updateModel(model);

  if (model->validate()) {
    model->UpdateEvent();

    IManagers* managers = SessionScopeMap::instance().get()->managers();
    managers->event_manager()->update(model->event());
    event_updated_.emit(model->event());

    auto validation_success = std::make_unique<Wt::WTemplate>(
        Wt::WString::tr("validation-success"));
    validation_success->bindString("text", "Событие успешно изменено");
    view_->bindWidget("validation-status", std::move(validation_success));
  } else {
    view_->bindEmpty("validation-status");
  }
  view_->updateView(model);
}

Wt::Signal<EventSptr>& EditEventDialog::event_updated() {
  return event_updated_;
}
} // namespace dialog
