#pragma once

#include <Wt/WColor.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDate.h>
#include <Wt/WTable.h>
#include <Wt/WTime.h>

#include <memory>
#include <string>

#include "event_d.hpp"

class EventW {
  public:
    EventW(int id, const std::string &title, Wt::WColor color, Wt::WDateTime begin, Wt::WDateTime end)
        : id_(id), title_(title), color_(color), begin_(begin), end_(end) {}

    ~EventW() = default;

    void makeEventWidget(Wt::WTable *table, Wt::WDate begin_of_week);

  private:
    int id_;
    std::string title_;
    Wt::WColor color_;
    Wt::WDateTime begin_;
    Wt::WDateTime end_;

    void makeEventPartWidget(std::string style_class, Wt::WTableCell *event_cell);
};
