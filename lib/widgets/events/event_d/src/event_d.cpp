#include "event_d.hpp"

#include <Wt/WBreak.h>
#include <Wt/WDialog.h>
#include <Wt/WImage.h>
#include <Wt/WText.h>

#include "Event.hpp"
#include "SessionScopeMap.hpp"

EventD::EventD(int id, std::string title) :
    Wt::WDialog(title),
    id_(id) {
    setClosable(true);
    rejectWhenEscapePressed();
    setMovable(false);
    setResizable(false);

    auto event = SessionScopeMap::instance().get()->managers()->event_manager()->get(id);

    contents()->addNew<Wt::WText>(event->start.toString("d MMMM yyyy H:mm") + Wt::WString(" - ") +
                                                       event->end.toString("d MMMM yyyy H:mm"));
    contents()->addNew<Wt::WBreak>();
    contents()->addNew<Wt::WText>(event->description);
    contents()->addNew<Wt::WBreak>();
    image_ = contents()->addNew<Wt::WImage>(Wt::WLink("/static/manul.webp"));
    image_->addStyleClass("img-fluid");
    contents()->addNew<Wt::WBreak>();
    // contents()->addNew<Wt::WImage>(Wt::WLink("/static/icons/chat.svg"));

    show();
}
