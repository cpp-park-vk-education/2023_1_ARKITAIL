#include "InPlaceEditTitle.hpp"

#include <Wt/WInPlaceEdit.h>
#include <Wt/WLineEdit.h>
#include <Wt/WString.h>

#include "SessionScopeMap.hpp"
#include "Managers.hpp"
#include "Profile.hpp"

InPlaceEditTitle::InPlaceEditTitle(std::string label, size_t profile_id) :
    Wt::WInPlaceEdit(false, label),
    id_(profile_id) {
    title_ = Wt::WString(label);
    setPlaceholderText("Название");
    lineEdit()->setMaxLength(30); // Илья
    valueChanged().connect(this, &InPlaceEditTitle::setTitle);
}

void InPlaceEditTitle::setTitle() {
    if (!text().empty() && text() != title_) {
        title_ = text();
        auto manager = SessionScopeMap::instance().get()->managers()->profile_manager();
        ProfileSptr profile = manager->get(id_);
        profile->name = title_.toUTF8();
        manager->update(profile);
    } else {
        setText(title_);
    }
}
