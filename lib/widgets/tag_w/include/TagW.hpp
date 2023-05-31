#pragma once

#include <Wt/WAnchor.h>

#include "Tag.hpp"

class TagW : public Wt::WAnchor {
  public:
    TagW(const Tag& tag);
    ~TagW() = default;

    Wt::Signal<Tag>& tagClicked();

  private:
    Wt::Signal<Tag> tag_clicked_;
    Tag tag_;
    
};
