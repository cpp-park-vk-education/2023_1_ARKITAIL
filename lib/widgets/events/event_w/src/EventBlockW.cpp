#include "EventBlockW.hpp"

EventBlockW::EventBlockW(const std::string& title, size_t id) :
    Wt::WPushButton(title),
    id_(id),
    title_(title) {}

void EventBlockW::setTitle(const std::string& title, size_t id) {
    std::cout << "\nSetTitle " << title << id  << "\n";
    if (id == id_) {
        setText(title);
    }
}

size_t EventBlockW::getId() {
    return id_;
}

const std::string& EventBlockW::getTitle() {
    return title_;
}
