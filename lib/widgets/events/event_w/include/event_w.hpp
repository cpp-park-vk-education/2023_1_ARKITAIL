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
    EventW(int id, const std::string& title, Wt::WColor color, Wt::WDateTime begin,
           Wt::WDateTime end) :
        id_(id),
        title_(title),
        color_(color),
        begin_(begin),
        end_(end) {}

    ~EventW() = default;

    void makeDayEventWidget(Wt::WTable* table, Wt::WDate day);
    void makeWeekEventWidget(Wt::WTable* table, Wt::WDate begin_of_week);
    void makeMonthEventWidget(Wt::WTable* table, Wt::WDate begin_of_month);

  private:
    int id_;
    std::string title_;
    Wt::WColor color_;
    Wt::WDateTime begin_;
    Wt::WDateTime end_;

    void addDialog(Wt::WPushButton* eventWidget);
    void makeEventLargePartWidget(std::string title, std::string style_class,
                                  Wt::WTableCell* event_cell);
    void makeEventSmallPartWidget(Wt::WTableCell* event_cell, std::string style_class);
};
