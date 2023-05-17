#include "event_w.hpp"

#include <Wt/WBreak.h>
#include <Wt/WColor.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WCssDecorationStyle.h>
#include <Wt/WDate.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>
#include <Wt/WTable.h>
#include <Wt/WTime.h>

#include <memory>
#include <string>

#include "event_d.hpp"

void EventW::makeEventWidget(Wt::WTable *table, Wt::WDate begin_of_week) {
    int dayWeek = begin_.date().dayOfWeek();
    if (begin_.date().daysTo(end_.date()) || end_.time().hour() - begin_.time().hour() == 24) {
        auto begin_event = begin_.date() > begin_of_week ? begin_.date() : begin_of_week;
        auto end_event =
            end_.date() < begin_of_week.addDays(6) ? end_.date() : begin_of_week.addDays(6);

        bool event_time = false;
        std::string base_style = "w-100 ";
        for (auto day = begin_of_week; day < begin_of_week.addDays(7); day = day.addDays(1)) {
            if (day == end_event) {
                auto style = base_style +
                             (day == begin_.date() ? "rounded-start" : "border-start-0") +
                             (std::string) " rounded-end";
                makeEventLargePartWidget("ㅤ", style, table->elementAt(1, day.dayOfWeek()));
                event_time = false;
            } else if (event_time) {
                auto style = base_style + (std::string) "border-start-0 border-end-0";
                makeEventLargePartWidget("ㅤ", style, table->elementAt(1, day.dayOfWeek()));
            } else if (day == begin_event) {
                auto style = base_style + (day == end_event ? "rounded-end" : "border-end-0") +
                             (std::string) " rounded-start";
                makeEventLargePartWidget(title_, style, table->elementAt(1, day.dayOfWeek()));
                event_time = true;
            } else {
                table->elementAt(1, day.dayOfWeek())->addWidget(std::make_unique<Wt::WBreak>());
            }
        }

    } else {
        for (int h = begin_.time().hour(); h <= end_.time().hour(); h++) {
            makeEventSmallPartWidget(table->elementAt(h + 2, dayWeek % 8));
        }
    }
}

void EventW::addDialog(Wt::WPushButton *eventWidget) {
    eventWidget->setAttributeValue("id", Wt::WString(std::to_string(id_)));
    eventWidget->setAttributeValue("title", Wt::WString(title_, Wt::CharEncoding::UTF8));
    eventWidget->clicked().connect([=] {
        eventWidget->addChild(
            std::make_unique<EventD>(std::stoi(eventWidget->attributeValue("id").toUTF8()),
                                     eventWidget->attributeValue("title").toUTF8()));
    });
}

void EventW::makeEventLargePartWidget(std::string title, std::string style_class,
                                      Wt::WTableCell *event_cell) {
    auto eventWidget = event_cell->addWidget(std::make_unique<Wt::WPushButton>(title));
    eventWidget->decorationStyle().setBackgroundColor(color_);
    eventWidget->setStyleClass("p-0 border-0 text-truncate btn btn-sm btn-light rounded-0 " +
                               style_class);
    addDialog(eventWidget);
}

void EventW::makeEventSmallPartWidget(Wt::WTableCell *event_cell) {
    auto eventWidget = event_cell->addWidget(std::make_unique<Wt::WPushButton>(title_));
    eventWidget->decorationStyle().setBackgroundColor(color_);
    eventWidget->setStyleClass(
        "p-1 px-2 m-1 border-0 text-truncate btn btn-sm btn-light rounded-0");
    addDialog(eventWidget);
    event_cell->addWidget(std::make_unique<Wt::WBreak>());
}
