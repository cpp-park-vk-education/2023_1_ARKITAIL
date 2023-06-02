#include "TagAnchorW.hpp"

#include <Wt/WLink.h>

#include "Managers.hpp"
#include "SessionScopeMap.hpp"
#include "Tag.hpp"

TagAnchorW::TagAnchorW(const Tag& tag) :
    Wt::WAnchor(Wt::WLink(Wt::LinkType::InternalPath, "/search"), tag.name),
    tag_(tag) {

    addStyleClass("btn btn-light border-success p-0 px-1 me-3 mt-1");
    clicked().connect([&] {
        tag_clicked_.emit(tag_);
    });

    auto cm = SessionScopeMap::instance().get()->connections_mediator();
    cm->search_tag.add_sender(&tag_clicked_);

}

Wt::Signal<const Tag&>& TagAnchorW::tagClicked() {
    return tag_clicked_;
}
