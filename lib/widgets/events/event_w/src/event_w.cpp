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
#include "time_utils.hpp"

void EventW::makeDayEventWidget(Wt::WTable* table) {
    std::cout << begin_.toString("dd MMMM yyyy") << ' ' << end_.toString("dd MMMM yyyy") << ' '
              << begin_.date().daysTo(end_.date()) << std::endl;
    if (begin_.date().daysTo(end_.date())) {
        auto style = "w-100 rounded-start rounded-end";
        makeEventLargePartWidget(title_, style, table->elementAt(0, 1));
    } else {
        for (int h = begin_.time().hour(); h <= end_.time().hour(); h++) {
            makeEventSmallPartWidget(table->elementAt(h + 1, 1), "");
        }
    }
}

void EventW::makeWeekEventWidget(Wt::WTable* table, Wt::WDate begin_of_week) {
    if (begin_.date().daysTo(end_.date())) {
        auto begin_event = begin_.date() > begin_of_week ? begin_.date() : begin_of_week;
        auto end_event = end_.date() < begin_of_week.addDays(TimeInterval::DAYS_IN_WEEK)
                             ? end_.date()
                             : begin_of_week.addDays(TimeInterval::DAYS_IN_WEEK - 1);

        bool event_time = false;
        std::string base_style = "w-100 ";
        for (auto day = begin_of_week; day < begin_of_week.addDays(TimeInterval::DAYS_IN_WEEK);
             day = day.addDays(1)) {
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
        int day_week = begin_.date().dayOfWeek();
        for (int h = begin_.time().hour(); h <= end_.time().hour(); h++) {
            makeEventSmallPartWidget(table->elementAt(h + 2, day_week + 1), "");
        }
    }
}

void EventW::makeMonthEventWidget(Wt::WTable* table, Wt::WDate day_of_month) {
    auto first_day_of_month = Wt::WDate(day_of_month.year(), day_of_month.month(), 1);
    auto first_day_of_table = first_day_of_month.addDays(1 - first_day_of_month.dayOfWeek());

    day_of_month = first_day_of_table;
    for (size_t pos = 0; day_of_month < first_day_of_table.addDays(TimeInterval::DAYS_IN_WEEK * 5);
         day_of_month = day_of_month.addDays(1), pos++) {
        if (begin_.date() <= day_of_month && day_of_month <= end_.date()) {
            std::string style, title = "ㅤ";  // ???
            if (day_of_month == begin_.date()) {
                style += "rounded-start ";
                title = title_;
            } else {
                style += "border-start-0 ";
            }
            style += (day_of_month == end_.date()) ? "rounded-end " : "border-end-0 ";
            makeEventLargePartWidget(
                title, style + "w-100",
                table->elementAt(1 + (pos) / TimeInterval::DAYS_IN_WEEK, day_of_month.dayOfWeek()));
        } else if (begin_.date().addDays(1 - begin_.date().dayOfWeek()) <= day_of_month &&
                   day_of_month <=
                       end_.date().addDays(TimeInterval::DAYS_IN_WEEK - end_.date().dayOfWeek())) {
            std::cout << day_of_month.toString("dd MMMM yyyy") << std::endl;

            std::cout << begin_.date().toString("dd MMMM yyyy") << ' '
                      << end_.date().toString("dd MMMM yyyy") << std::endl;

            std::cout
                << begin_.date().addDays(1 - begin_.date().dayOfWeek()).toString("dd MMMM yyyy")
                << ' '
                << end_.date()
                       .addDays(TimeInterval::DAYS_IN_WEEK - end_.date().dayOfWeek())
                       .toString("dd MMMM yyyy")
                << std::endl;
            table->elementAt(1 + (pos) / TimeInterval::DAYS_IN_WEEK, day_of_month.dayOfWeek())
                ->addWidget(std::make_unique<Wt::WBreak>());
        }
    }
}

void EventW::addDialog(Wt::WPushButton* eventWidget) {
    eventWidget->setAttributeValue("id", Wt::WString(std::to_string(id_)));
    eventWidget->setAttributeValue("title", Wt::WString(title_, Wt::CharEncoding::UTF8));
    eventWidget->clicked().connect([=] {
        eventWidget->addChild(
            std::make_unique<EventD>(std::stoi(eventWidget->attributeValue("id").toUTF8()),
                                     eventWidget->attributeValue("title").toUTF8()));
    });
}

void EventW::makeEventLargePartWidget(std::string title, std::string style_class,
                                      Wt::WTableCell* event_cell) {
    auto eventWidget = event_cell->addWidget(std::make_unique<Wt::WPushButton>(title));
    eventWidget->decorationStyle().setBackgroundColor(color_);
    eventWidget->setStyleClass(
        "d-block p-0 border-1 text-truncate btn btn-sm btn-light rounded-0 " + style_class);
    addDialog(eventWidget);
}

void EventW::makeEventSmallPartWidget(Wt::WTableCell* event_cell, std::string style_class) {
    auto eventWidget = event_cell->addWidget(std::make_unique<Wt::WPushButton>(title_));
    eventWidget->decorationStyle().setBackgroundColor(color_);
    eventWidget->setStyleClass(
        "p-1 px-2 m-1 border-0 text-truncate btn btn-sm btn-light rounded-0" + style_class);
    addDialog(eventWidget);
    if (style_class != " d-inline") {
        event_cell->addWidget(std::make_unique<Wt::WBreak>());
    }
}
