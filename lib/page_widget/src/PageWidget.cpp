#include <Wt/WLink.h>
#include <Wt/WText.h>
#include <Wt/WAnchor.h>

#include <memory>
#include <string>

#include "PageWidget.hpp"

PageWidget::PageWidget(const std::string& path) :
	Wt::WContainerWidget(),
	anchor_(nullptr) {

	anchor_ = addWidget(std::make_unique<Wt::WAnchor>(Wt::WLink(Wt::LinkType::InternalPath, path), path));
}

void PageWidget::init() {}

