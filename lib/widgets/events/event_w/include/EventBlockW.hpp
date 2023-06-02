#pragma once

#include <Wt/WPushButton.h>

class EventBlockW : public Wt::WPushButton {
  public:
    EventBlockW(const std::string& title, size_t id);
    ~EventBlockW() = default;

    void setTitle(const std::string& title, size_t id);
    size_t getId();
    const std::string& getTitle();

  private:
    size_t id_;
    std::string title_;

};
