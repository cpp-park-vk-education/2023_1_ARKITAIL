#pragma once

#include <Wt/WAnchor.h>

#include "Tag.hpp"

class TagAnchorW : public Wt::WAnchor {
  public:
    TagAnchorW(const Tag& tag);
    ~TagAnchorW() = default;

    Wt::Signal<Tag>& tagClicked();

  private:
    Wt::Signal<Tag> tag_clicked_;
    Tag tag_;
    
};
