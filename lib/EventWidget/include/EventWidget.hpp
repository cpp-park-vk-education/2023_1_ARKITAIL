#pragma once

#include <Wt/WColor.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDate.h>
#include <Wt/WTable.h>
#include <Wt/WTime.h>

#include <memory>
#include <string>

class EventWidget {
  public:
    EventWidget(int id, const std::string &title, Wt::WColor color, Wt::WDateTime begin, Wt::WDateTime end)
        : id_(id), title_(title), color_(color), begin_(begin), end_(end) {}

    ~EventWidget() = default;

    void makeEventWidget(Wt::WTable *table, Wt::WDate begin_of_week);

  private:
    int id_;
    std::string title_;
    Wt::WColor color_;
    Wt::WDateTime begin_;
    Wt::WDateTime end_;

    std::unique_ptr<Wt::WContainerWidget> makeEventPartWidget(std::string style_class);
};
