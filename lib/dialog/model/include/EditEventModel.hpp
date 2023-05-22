#pragma once

#include "EventModel.hpp"

namespace dialog {
class EditEventModel : public EventModel {
 public:
  explicit EditEventModel(EventSptr event);

  void UpdateEvent() override;
 private:
  void SetValues() override;
};
} // namespace dialog
