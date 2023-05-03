#pragma once

#include <Wt/WColor.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WCssDecorationStyle.h>
#include <Wt/WDate.h>
#include <Wt/WPushButton.h>
#include <Wt/WTable.h>
#include <Wt/WTime.h>

#include <string>

class Event {
  private:
    int id;
    std::string title;
    std::string desc;
    Wt::WColor color;
    Wt::WDateTime begin;
    Wt::WDateTime end;

    std::unique_ptr<Wt::WContainerWidget> makeBigEventtWidget(std::string style_class);
    std::unique_ptr<Wt::WContainerWidget> makeSmallEventWidget(std::string style_class);

  public:
    Event(int id_, const std::string &title_, std::string &desc_, Wt::WColor color_, Wt::WDateTime begin_,
          Wt::WDateTime end_)
        : id(id_), title(title_), desc(desc_), color(color_), begin(begin_), end(end_) {}

    Event(int id_, const std::string &title_, Wt::WColor color_, Wt::WDateTime begin_, Wt::WDateTime end_)
        : id(id_), title(title_), color(color_), begin(begin_), end(end_) {}

    void makeEventWidgets(Wt::WTable *table_, Wt::WDate beginWeek);
};
