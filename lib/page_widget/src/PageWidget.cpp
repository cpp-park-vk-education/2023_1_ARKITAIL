#include "PageWidget.hpp"

#include <Wt/WAnchor.h>
#include <Wt/WLink.h>
#include <Wt/WText.h>

#include <memory>
#include <string>

#include "ConnectionPoint.hpp"
#include "ConnectionsMediator.hpp"

PageWidget::PageWidget() : Wt::WContainerWidget(), triggered_() {
    ConnectionsMediator::instance().cp.add_sender(&triggered_);
    ConnectionsMediator::instance().cp.add_receiver(this, &PageWidget::triggered);
}

void PageWidget::trigger() { triggered_.emit(831); }

void PageWidget::triggered(int arg) { std::cout << "Received signal " << arg << std::endl; }

void PageWidget::init() {}
