#include "EventDialog.hpp"

#include <memory>

#include <Wt/WDialog.h>
#include <Wt/WObject.h>

#include "Calendar.hpp"
#include "Event.hpp"
#include "EventView.hpp"

// по умолчанию event = nullptr
void EventDialog::Show(
    Wt::WObject* parent,
    std::vector<CalendarSptr> public_calendars,
    std::vector<CalendarSptr> private_calendars,
    EventSptr event) {
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
