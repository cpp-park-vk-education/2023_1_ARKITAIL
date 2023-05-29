#include "TagW.hpp"

#include <Wt/WLink.h>

#include "Tag.hpp"

TagW::TagW(Tag tag) {
    addWidget(
        std::make_unique<Wt::WAnchor>(Wt::WLink(Wt::LinkType::InternalPath, "/search"), tag.name));
    addStyleClass("btn btn-light border-success p-0 px-1 mx-1");
    clicked().connect([=] {
        tag_clicked_.emit(tag.id);
    });
}

Wt::Signal<size_t>& TagW::tagClicked() {
    return tag_clicked_;
}
