#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WSignal.h>
#include <Wt/WString.h>
#include <Wt/WText.h>

template<typename T>
class ItemW : public Wt::WPushButton {
public:
	ItemW(size_t id, const std::string& title, const T& obj);
	Wt::Signal<T>* item_clicked();
	size_t getId();

protected:
	Wt::Signal<T> clicked_;
	T obj_;
	size_t id_;
};

template<typename T>
ItemW<T>::ItemW(size_t id, const std::string& title, const T& obj) :
	clicked_(),
	obj_(obj),
	id_(id) {

	setText(Wt::WString(title));

	clicked().connect([this](){
		this->clicked_.emit(this->obj_);
	});
}

template<typename T>
Wt::Signal<T>* ItemW<T>::item_clicked() {
	return &clicked_;
}

template<typename T>
size_t ItemW<T>::getId() {
	return id_;
}
