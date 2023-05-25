#pragma once

#include "EventModel.hpp"

namespace dialog {
class CreateEventModel : public EventModel {
 public:
  CreateEventModel();

  void UpdateEvent() override;
 private:
  void SetValues() override;
};
} // namespace dialog
