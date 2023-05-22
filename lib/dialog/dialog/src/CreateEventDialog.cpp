#include "CreateEventDialog.hpp"

#include <memory>

#include <Wt/WObject.h>

#include "CreateEventView.hpp"

namespace dialog {
CreateEventDialog::CreateEventDialog(Wt::WObject* parent) {
  parent_ = parent;
  contents_ = std::make_unique<CreateEventView>();
  title_ = "Событие";
  min_width_ = 600;
  min_height_ = 600;
}
} // namespace dialog
