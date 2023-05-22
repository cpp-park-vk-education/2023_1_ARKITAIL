#include "event_d.hpp"

#include "Wt/WBreak.h"
#include "Wt/WDialog.h"
#include "Wt/WImage.h"
#include "Wt/WText.h"

EventD::EventD(int id, std::string title) :
    Wt::WDialog(title),
    id_(id) {
    setClosable(true);
    rejectWhenEscapePressed();
    setMovable(false);
    setResizable(false);
    // как-то получить информацию о событии по id(только )

    contents()->addNew<Wt::WText>("Тут дата1 - тут дата2");
    contents()->addNew<Wt::WBreak>();
    contents()->addNew<Wt::WText>("Описание какое-то");
    contents()->addNew<Wt::WBreak>();
    image_ = contents()->addNew<Wt::WImage>(Wt::WLink("/static/manul.webp"));
    image_->addStyleClass("img-fluid");
    contents()->addNew<Wt::WBreak>();
    // contents()->addNew<Wt::WImage>(Wt::WLink("/static/icons/chat.svg"));

    show();
}