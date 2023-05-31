#pragma once

#include <Wt/WAnchor.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WImage.h>
#include <Wt/WText.h>

#include <vector>

#include "Calendar.hpp"
#include "TagW.hpp"
#include "User.hpp"
#include "Node.hpp"


class CalendarCardW : public Wt::WContainerWidget {
  public:
    CalendarCardW();
    CalendarCardW(const User& user, CalendarSptr calendar, const std::vector<Tag>& tags);

  private:
    Wt::WAnchor* title_;
    Wt::WText* descriptions_;
    std::vector<TagW*> tags_;
    Wt::WAnchor* username_;
    Node node_;

    Wt::Signal<const Node&> calendar_clicked_;
};
