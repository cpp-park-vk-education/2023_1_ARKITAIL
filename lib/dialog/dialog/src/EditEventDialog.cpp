#include "EditEventDialog.hpp"

#include <Wt/WObject.h>

#include "EditEventView.hpp"
#include "Event.hpp"

namespace dialog {
EditEventDialog::EditEventDialog(Wt::WObject* parent, EventSptr event) {
  parent_ = parent;
  contents_ = std::make_unique<EditEventView>(event);
  title_ = "Событие";
  min_width_ = 600;
  min_height_= 600;
}
} // namespace dialog
