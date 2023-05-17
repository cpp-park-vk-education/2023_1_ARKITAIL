#include "calendar_header_w.hpp"

#include <Wt/WComboBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDate.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>
#include <Wt/WText.h>
#include <Wt/WTime.h>

#include <memory>

CalendarHeaderW::CalendarHeaderW() {
    selected_date_ = std::make_unique<Wt::WDate>(std::chrono::system_clock::now());
    auto button_box = addNew<Wt::WContainerWidget>();
    button_box->addStyleClass("my-2 me-2 my-lg-0 d-flex justify-content-center");
    today_button_ = button_box->addNew<Wt::WPushButton>("Сегодня");
    prev_button_ = button_box->addNew<Wt::WPushButton>("<");
    next_button_ = button_box->addNew<Wt::WPushButton>(">");
    calendar_title_ = button_box->addNew<Wt::WText>(makeTitle());

    container_option_range_ = addNew<Wt::WContainerWidget>();

    container_option_range_->addStyleClass("d-flex row");
    option_range_ = container_option_range_->addNew<Wt::WComboBox>();
    option_range_->addItem("Месяц");
    option_range_->addItem("Неделя");
    option_range_->addItem("День");
    option_range_->setCurrentIndex(1);

    today_button_->clicked().connect(this, &CalendarHeaderW::switchToToday);
    prev_button_->clicked().connect(this, &CalendarHeaderW::switchToPrev);
    next_button_->clicked().connect(this, &CalendarHeaderW::switchToNext);
    option_range_->changed().connect(this, &CalendarHeaderW::setRange);
    addStyle();
}

Wt::WString CalendarHeaderW::makeTitle() {
    if (range_ == Range::DAY) {
        return selected_date_->toString("dd MMMM");
    }
    return selected_date_->toString("MMMM yyyy");
}

void CalendarHeaderW::addStyle() {
    addStyleClass("d-flex flex-column flex-lg-row justify-content-center align-items-center my-3");
    today_button_->addStyleClass("mx-2 btn-light");
    prev_button_->addStyleClass("mx-1 btn-light");
    next_button_->addStyleClass("mx-2 btn-light");
    calendar_title_->addStyleClass("mx-3 h2");
    option_range_->addStyleClass("col mx-3");
}

void CalendarHeaderW::setRange() {
    range_ = Range(option_range_->currentIndex());
    change_range_.emit(range_);
    change_selected_date_.emit(
        Wt::WDate(selected_date_->year(), selected_date_->month(), selected_date_->day()));
    calendar_title_->setText(makeTitle());
}

void CalendarHeaderW::switchToToday() {
    selected_date_ = std::make_unique<Wt::WDate>(std::chrono::system_clock::now());
    change_selected_date_.emit(
        Wt::WDate(selected_date_->year(), selected_date_->month(), selected_date_->day()));
    calendar_title_->setText(makeTitle());
}

void CalendarHeaderW::switchToPrev() {
    switch (range_) {
        case Range::DAY:
            selected_date_ = std::make_unique<Wt::WDate>(selected_date_->addDays(-1));
            break;
        case Range::WEEK:
            selected_date_ = std::make_unique<Wt::WDate>(selected_date_->addDays(-7));
            break;
        case Range::MONTH:
            selected_date_ = std::make_unique<Wt::WDate>(selected_date_->addMonths(-1));
            break;
    }
    change_selected_date_.emit(
        Wt::WDate(selected_date_->year(), selected_date_->month(), selected_date_->day()));
    calendar_title_->setText(makeTitle());
}

void CalendarHeaderW::switchToNext() {
    switch (range_) {
        case Range::DAY:
            selected_date_ = std::make_unique<Wt::WDate>(selected_date_->addDays(1));
            break;
        case Range::WEEK:
            selected_date_ = std::make_unique<Wt::WDate>(selected_date_->addDays(7));
            break;
        case Range::MONTH:
            selected_date_ = std::make_unique<Wt::WDate>(selected_date_->addMonths(1));
            break;
    }
    change_selected_date_.emit(
        Wt::WDate(selected_date_->year(), selected_date_->month(), selected_date_->day()));
    calendar_title_->setText(makeTitle());
}

void CalendarHeaderW::addConnections() {}
