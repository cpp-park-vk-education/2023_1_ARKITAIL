#include "event_d.hpp"

#include <Wt/WBreak.h>
#include <Wt/WDialog.h>
#include <Wt/WText.h>
#include <Wt/WPushButton.h>

#include "Event.hpp"
#include "SessionScopeMap.hpp"

EventD::EventD(size_t id, std::string title) :
    Wt::WDialog(title),
    id_(id) {
    setClosable(true);
    rejectWhenEscapePressed();
    setMovable(false);
    setResizable(false);

    auto ss = SessionScopeMap::instance().get();
    auto event = ss->managers()->event_manager()->get(id);

    dates_ =
        contents()->addNew<Wt::WText>(event->start.toString("d MMMM yyyy H:mm") +
                                      Wt::WString("<b> - </b>") + event->end.toString("d MMMM yyyy H:mm"));
    dates_->addStyleClass("d-block");
    description_ = contents()->addNew<Wt::WText>( "<b>Описание: </b>" + event->description);
    description_->addStyleClass("d-block");
    contents()->addNew<Wt::WBreak>();
    contents()->addNew<Wt::WBreak>();
    edit_button_ = contents()->addNew<Wt::WPushButton>("Редактировать");
    edit_button_->addStyleClass("m-2 mx-auto w-50 position-absolute translate-middle-x start-50 bottom-0");
    edit_button_->clicked().connect(this, &EventD::edit);

    ss->connections_mediator()->edit_event_title.add_sender(&event_edited_);

    show();
}

void EventD::edit() {
    std::cout << "\nedit\n";
    std::string new_title = "TYPIC";
    
    // SessionScopeMap::instance().get()->managers()->event_manager()->update();
    event_edited_.emit(new_title, id_);
    std::cout << "\nTYPIC emit\n";
}
