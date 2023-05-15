#include "day_w.hpp"

#include "event_w.hpp"

DayW::DayW() { std::cout << "\n\ndayMake\n" << std::endl; }

void DayW::update(Wt::WDate selected_date_) {
    auto selected_date =
        std::make_unique<Wt::WDate>(selected_date_.year(), selected_date_.month(), selected_date_.day());
    table_->clear();
    table_->setHeaderCount(1, Wt::Orientation::Vertical);
    makeHeaderTime();
    table_->insertColumn(1);
    // table_->elementAt(0, 1)->addWidget(std::make_unique<Wt::WText>("ur"));
}
