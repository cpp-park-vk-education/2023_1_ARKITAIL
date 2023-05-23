#include "EditEventView.hpp"

#include "EditEventModel.hpp"

namespace dialog {
EditEventView::EditEventView(EventSptr event)
    : EventView(std::make_shared<EditEventModel>(event)) {
}
} // namespace dialog
