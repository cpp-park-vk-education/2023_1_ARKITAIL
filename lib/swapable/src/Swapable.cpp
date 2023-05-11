#include <memory>

#include "Swapable.hpp"
#include "PageWidget.hpp"

Swapable::Swapable() :
	destination_(nullptr),
	content_() {}

Swapable::Swapable(std::unique_ptr<PageWidget> content) :
	Swapable() {

	content_.swap(content);
}

void Swapable::swap() {
	content_.swap(destination_->content_);
}

void Swapable::set_destination(Swapable* destination) {
	destination_ = destination;
}

void Swapable::build_destination() {
	destination_->destination_ = this;
}

