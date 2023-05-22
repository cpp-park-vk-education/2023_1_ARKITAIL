#include "Dialog.hpp"

#include <string>
#include <utility>

#include <Wt/WDialog.h>
#include <Wt/WObject.h>

namespace dialog {
void Dialog::Show() {
  auto dialog = parent_->addChild(std::make_unique<Wt::WDialog>());

  dialog->setWindowTitle(title_);
  dialog->setMovable(false);
  dialog->setClosable(true);
  dialog->setMinimumSize(min_width_, min_height_);
  dialog->contents()->addWidget(std::move(contents_));

  dialog->finished().connect([=]{
    parent_->removeChild(dialog);
  });

  dialog->show();
}
} // namespace dialog
