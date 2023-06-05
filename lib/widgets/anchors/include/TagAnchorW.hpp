#pragma once

#include <Wt/WAnchor.h>

#include "Tag.hpp"

class TagAnchorW : public Wt::WAnchor {
  public:
    TagAnchorW(const Tag& tag);
    ~TagAnchorW() = default;

    Wt::Signal<const Tag&>& tagClicked();

  private:
    Wt::Signal<const Tag&> tag_clicked_;
    Tag tag_;
    
};
