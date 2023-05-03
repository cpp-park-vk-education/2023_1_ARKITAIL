#include "MainWidget.hpp"

#include "CalendarWidget.hpp"

MainWidget::MainWidget() { calendar_ = addWidget(std::make_unique<CalendarWidget>()); }
