#pragma once

#include <Wt/WInPlaceEdit.h>

class InPlaceEditTitle : public Wt::WInPlaceEdit {
  public:
    InPlaceEditTitle(std::string label, size_t profile_id);
    ~InPlaceEditTitle() = default;
    void setTitle();

  private:
    Wt::WString title_;
    size_t id_;
};
