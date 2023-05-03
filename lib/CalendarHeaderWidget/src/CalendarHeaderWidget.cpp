#include "CalendarHeaderWidget.hpp"

#include <Wt/WComboBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDate.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>
#include <Wt/WText.h>
#include <Wt/WTime.h>

#include <memory>

#include "utils.hpp"

CalendarHeaderWidget::CalendarHeaderWidget() {
    selected_date_ = std::make_unique<Wt::WDate>(std::chrono::system_clock::now());
    auto button_box = addNew<Wt::WContainerWidget>();
    button_box->addStyleClass("my-2 me-2 my-lg-0 d-flex justify-content-center");
    today_button_ = button_box->addNew<Wt::WPushButton>("Сегодня");
    prev_button_ = button_box->addNew<Wt::WPushButton>("<");
    next_button_ = button_box->addNew<Wt::WPushButton>(">");
    calendar_title_ = button_box->addNew<Wt::WText>(makeTitle());

    auto container_option_range = addNew<Wt::WContainerWidget>();

    container_option_range->addStyleClass("d-flex ms-3 row");
    option_range_ = container_option_range->addNew<Wt::WComboBox>();
    option_range_->addItem("Месяц");
    option_range_->addItem("Неделя");
    option_range_->addItem("День");
    option_range_->setCurrentIndex(1);

    addStyle();
}

Wt::WString CalendarHeaderWidget::makeTitle() { return selected_date_->toString("MMMM yyyy"); }

void CalendarHeaderWidget::addStyle() {
    addStyleClass("d-flex flex-column flex-lg-row justify-content-center align-items-center my-3");
    today_button_->addStyleClass("mx-2 btn-light");
    prev_button_->addStyleClass("mx-1 btn-light");
    next_button_->addStyleClass("mx-2 btn-light");
    calendar_title_->addStyleClass("mx-3 h2");
    option_range_->addStyleClass("col mx-3");
}

void CalendarHeaderWidget::setRange(Range new_range) {
    range_ = new_range;
    change_range_.emit(new_range);
    selected_date_ = std::make_unique<Wt::WDate>(std::chrono::system_clock::now());
    change_selected_date_.emit(
        std::make_unique<Wt::WDate>(selected_date_->year(), selected_date_->month(), selected_date_->day()));
}

void CalendarHeaderWidget::switchToToday() {}

void CalendarHeaderWidget::switchToPrev() {}

void CalendarHeaderWidget::switchToNext() {}

void CalendarHeaderWidget::addConnections() {}