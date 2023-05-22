#pragma once

#include <memory>

#include <Wt/WObject.h>
#include <Wt/WWidget.h>

namespace dialog {
class Dialog {
 public:
  void Show();

 protected:
  Dialog() = default;

  Wt::WObject* parent_;
  std::unique_ptr<Wt::WWidget> contents_;
  std::string title_;
  size_t min_width_;
  size_t min_height_;
};
} // namespace dialog
