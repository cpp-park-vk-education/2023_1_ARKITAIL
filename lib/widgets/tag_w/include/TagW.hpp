#pragma once

#include <Wt/WAnchor.h>
#include <Wt/WContainerWidget.h>

#include "Tag.hpp"

class TagW : public Wt::WContainerWidget {
  public:
    TagW(Tag tag);
    ~TagW() = default;
    Wt::Signal<size_t>& tagClicked();

  private:
    Wt::Signal<size_t> tag_clicked_;
};
