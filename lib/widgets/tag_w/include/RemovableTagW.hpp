#pragma once

#include <Wt/WPushButton.h>

#include "TagW.hpp"

class RemovableTagW : public TagW {
  public:
    RemovableTagW(Tag tag);
    ~RemovableTagW() = default;

  private:
    Wt::WPushButton* remove_button_;
};
