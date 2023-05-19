#include "event_dialog.hpp"

#include <memory>

#include <Wt/WDialog.h>
#include <Wt/WObject.h>

#include "calendar.hpp"
#include "event.hpp"
#include "event_view.hpp"

// по умолчанию event = nullptr
void EventDialog::Show(
    Wt::WObject* parent,
    std::vector<std::shared_ptr<Calendar>> public_calendars,
    std::vector<std::shared_ptr<Calendar>> private_calendars,
    std::shared_ptr<Event> event) {
  auto dialog = parent->addChild(std::make_unique<Wt::WDialog>());

  dialog->setWindowTitle("Событие");
  dialog->setMovable(false);
  dialog->setClosable(true);
  dialog->setMinimumSize(600, 600);

  dialog->contents()->addWidget(
      std::make_unique<EventView>(public_calendars, private_calendars, event));

  dialog->finished().connect([=]{
    parent->removeChild(dialog);
  });

  dialog->show();
}
