#include "event_w.hpp"

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
    if (begin_.date().daysTo(end_.date())) {
        auto day = begin_.date() > begin_of_week ? begin_.date() : begin_of_week;
        makeEventPartWidget("w-100 text-nowrap rounded-start border-end-0", table->elementAt(1, day.dayOfWeek()));

        day = day.addDays(1);
        for (; day < end_.date() && day < begin_of_week.addDays(7); day = day.addDays(1)) {
            makeEventPartWidget("w-100 text-nowrap border-start-0 border-end-0", table->elementAt(1, day.dayOfWeek()));
        }
        if (day <= end_.date() && day < begin_of_week.addDays(7))
            makeEventPartWidget("w-100 text-nowrap rounded-end border-start-0", table->elementAt(1, day.dayOfWeek()));

    } else {
        int h = begin_.time().hour();
        makeEventPartWidget("text-wrap rounded-top border-bottom-0", table->elementAt(h + 2, dayWeek % 8));
        h++;
        for (; h < end_.time().hour() - 1; h++) {
            makeEventPartWidget("text-wrap border-top-0 border-bottom-0", table->elementAt(h + 2, dayWeek % 8));
        }
        makeEventPartWidget("text-wrap rounded-bottom border-top-0", table->elementAt(h + 2, dayWeek % 8));
    }
}

void EventW::makeEventPartWidget(std::string style_class, Wt::WTableCell *event_cell) {
    auto eventWidget = event_cell->addWidget(std::make_unique<Wt::WPushButton>(title_));
    eventWidget->decorationStyle().setBackgroundColor(color_);
    eventWidget->setStyleClass("btn btn-sm btn-light rounded-0 " + style_class);
    eventWidget->setAttributeValue("id", Wt::WString(std::to_string(id_)));
    eventWidget->setAttributeValue("title", Wt::WString(title_, Wt::CharEncoding::UTF8));
    eventWidget->clicked().connect([=] {
        eventWidget->addChild(std::make_unique<EventD>(std::stoi(eventWidget->attributeValue("id").toUTF8()),
                                                       eventWidget->attributeValue("title").toUTF8()));
    });
}
