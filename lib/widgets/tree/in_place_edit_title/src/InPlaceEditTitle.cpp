#include "InPlaceEditTitle.hpp"

#include <Wt/WInPlaceEdit.h>
#include <Wt/WLineEdit.h>
#include <Wt/WString.h>

InPlaceEditTitle::InPlaceEditTitle(std::string label) :
    Wt::WInPlaceEdit(false, label) {
    title_ = Wt::WString(label);
    setPlaceholderText("Название");
    lineEdit()->setMaxLength(15);
    valueChanged().connect(this, &InPlaceEditTitle::setTitle);
}

void InPlaceEditTitle::setTitle() {
    if (!text().empty() && text() != title_ && text().toUTF8().length() <= 15) {
        title_ = text();
        // отправить что-то Сене
    } else {
        setText(title_);
    }
}
