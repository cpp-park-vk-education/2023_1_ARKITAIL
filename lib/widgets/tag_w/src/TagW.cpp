#include "TagW.hpp"

#include <Wt/WLink.h>

#include "Managers.hpp"
#include "SessionScopeMap.hpp"
#include "Tag.hpp"

TagW::TagW(const Tag& tag) :
    Wt::WAnchor(Wt::WLink(Wt::LinkType::InternalPath, "/search"), tag.name),
    tag_(tag) {

    addStyleClass("btn btn-light border-success p-0 px-1 me-3");
    clicked().connect([&] {
        tag_clicked_.emit(tag_);
    });

    auto cm = SessionScopeMap::instance().get()->connections_mediator();
    cm->search_tag.add_sender(&tag_clicked_);

}

Wt::Signal<Tag>& TagW::tagClicked() {
    return tag_clicked_;
}
