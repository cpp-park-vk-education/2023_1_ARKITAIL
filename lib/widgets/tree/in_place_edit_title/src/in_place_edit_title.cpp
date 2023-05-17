#include "in_place_edit_title.hpp"

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
    if (text() != Wt::WString("") && text() != title_) {
        title_ = text();
        // отправить что-то Сене
        std::cout << title_.toUTF8() << std::endl;
    } else {
        setText(title_);
    }
}
