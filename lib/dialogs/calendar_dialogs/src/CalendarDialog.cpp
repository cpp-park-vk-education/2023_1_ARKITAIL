#include "CalendarDialog.hpp"

#include <memory>

#include <Wt/WDialog.h>
#include <Wt/WObject.h>
#include <Wt/WWidget.h>

void CalendarDialog::ShowInternal(
    Wt::WObject* parent,
    std::unique_ptr<Wt::WWidget>&& contents) {
  auto dialog = parent->addChild(std::make_unique<Wt::WDialog>());

  dialog->setWindowTitle("Календарь");
  dialog->setMovable(false);
  dialog->setClosable(true);
  dialog->setMinimumSize(600, 600);

  dialog->contents()->addWidget(std::move(contents));

  dialog->finished().connect([=]{
    parent->removeChild(dialog);
  });

  dialog->show();
}
