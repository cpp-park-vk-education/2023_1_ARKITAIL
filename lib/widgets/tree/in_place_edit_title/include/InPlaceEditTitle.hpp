#pragma once

#include <Wt/WInPlaceEdit.h>

class InPlaceEditTitle : public Wt::WInPlaceEdit {
  public:
    InPlaceEditTitle(std::string label);
    ~InPlaceEditTitle() = default;
    void setTitle();

  private:
    Wt::WString title_;
};
