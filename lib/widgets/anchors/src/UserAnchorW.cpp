#include "UserAnchorW.hpp"

#include <Wt/WLink.h>

#include "Managers.hpp"
#include "SessionScopeMap.hpp"
#include "User.hpp"

UserAnchorW::UserAnchorW(const std::string prefix, const User& user) :
    Wt::WAnchor(Wt::WLink(Wt::LinkType::InternalPath, "/other_calendar"),
               prefix + user.nickname),
    user_(user) {

    addStyleClass("d-block text-decoration-none fw-bolder");

    SessionScopeMap::instance().get()->connections_mediator()->set_tree_root.add_sender(
        &user_clicked_);

    clicked().connect([&] {
        auto mgr = SessionScopeMap::instance().get()->managers();

        // переделать на ноду паблик групп
        std::cout << "\nemit signal USER" << user_.root_id <<"\n\n";
        user_clicked_.emit(*mgr->node_manager()->get(16), user_);
    });

}
