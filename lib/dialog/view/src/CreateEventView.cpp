#include "CreateEventView.hpp"

#include "CreateEventModel.hpp"

namespace dialog {
CreateEventView::CreateEventView()
    : EventView(std::make_shared<CreateEventModel>()) {
}
} // namespace dialog
