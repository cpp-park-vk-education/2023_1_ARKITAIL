#include "UserAnchorW.hpp"

#include <Wt/WLink.h>

#include "Managers.hpp"
#include "SessionScopeMap.hpp"
#include "User.hpp"

UserAnchorW::UserAnchorW(const User& user) :
    Wt::WAnchor(Wt::WLink(Wt::LinkType::InternalPath, "/other_profile"), "<b>Автор:</b> " + user.nickname),
    user_(user) {

    addStyleClass("d-block text-decoration-none fw-bolder");
    clicked().connect([&] {
        user_clicked_.emit(user_);
    });

    auto cm = SessionScopeMap::instance().get()->connections_mediator();
    cm->swap_to_profile_page.add_sender(&user_clicked_);

}

