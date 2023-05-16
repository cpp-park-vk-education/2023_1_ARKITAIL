#include <Wt/WAnchor.h>
#include <Wt/WLink.h>
#include <Wt/WText.h>

#include <memory>
#include <string>

#include "ConnectionPoint.hpp"
#include "ConnectionsMediator.hpp"
#include "PageWidget.hpp"

PageWidget::PageWidget(const std::string& path) :
	Wt::WContainerWidget(),
	anchor_(nullptr),
	triggered_() {

	anchor_ = addWidget(std::make_unique<Wt::WAnchor>(Wt::WLink(Wt::LinkType::InternalPath, path), path));

	//ConnectionsMediator::instance().cp.add_sender(&triggered_);
	//ConnectionsMediator::instance().cp.add_receiver(this, &PageWidget::triggered);
}

void PageWidget::trigger() { triggered_.emit(831); }

void PageWidget::triggered(int arg) { std::cout << "Received signal " << arg << std::endl; }

void PageWidget::init() {}
