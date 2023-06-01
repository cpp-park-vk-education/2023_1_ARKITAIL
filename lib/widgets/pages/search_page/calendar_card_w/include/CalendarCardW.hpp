#pragma once

#include <Wt/WAnchor.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WImage.h>
#include <Wt/WText.h>

#include <vector>

#include "Calendar.hpp"
#include "TagAnchorW.hpp"
#include "User.hpp"
#include "Node.hpp"


class CalendarCardW : public Wt::WContainerWidget {
  public:
    CalendarCardW();
    CalendarCardW(const User& user, CalendarSptr calendar, const std::vector<Tag>& tags);

  private:
    Wt::WAnchor* title_;
    Wt::WImage* avatar_;
    Wt::WAnchor* username_;
    Wt::WText* description_;
    std::vector<TagAnchorW*> tags_;
    Node node_;
    User user_;

    Wt::Signal<const Node&, const User&> calendar_clicked_;
};
