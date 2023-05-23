#include "CreateEventDialog.hpp"

#include <memory>

#include <Wt/WDialog.h>
#include <Wt/WLogger.h>
#include <Wt/WPushButton.h>

#include "Calendar.hpp"
#include "CreateEventView.hpp"
#include "Event.hpp"
#include "IManagers.hpp"
#include "SessionScopeMap.hpp"

namespace dialog {
CreateEventDialog::CreateEventDialog()
    : Wt::WDialog("Событие") {
  rejectWhenEscapePressed();
  setClosable(true);
  setMinimumSize(700, 800);
  setMovable(false);

  view_ = contents()->addNew<CreateEventView>();

  Wt::WPushButton* submit = footer()->addNew<Wt::WPushButton>("OK");
  submit->clicked().connect(this, &CreateEventDialog::HandleInput);
}

void CreateEventDialog::HandleInput() {
  EventModel* model = view_->model().get();
  view_->updateModel(model);

  if (model->validate()) {
    model->UpdateEvent();

    IManagers* managers = SessionScopeMap::instance().get()->managers();
    size_t event_id = managers->event_manager()->add(model->event());
    event_created_.emit(managers->event_manager()->get(event_id));

    model->reset();
    model->set_event(nullptr);
  }

  view_->updateView(model);
}

Wt::Signal<EventSptr>& CreateEventDialog::event_created() {
  return event_created_;
}
} // namespace dialog
