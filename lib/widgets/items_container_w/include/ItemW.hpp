#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WSignal.h>
#include <Wt/WString.h>
#include <Wt/WText.h>

template<typename T>
class ItemW : public Wt::WPushButton {
public:
	ItemW(const std::string& title, const T& obj);
	Wt::Signal<T>* item_clicked();

protected:
	Wt::Signal<T> clicked_;
	T obj_;

};

template<typename T>
ItemW<T>::ItemW(const std::string& title, const T& obj) :
	clicked_(),
	obj_(obj) {

	setText(Wt::WString(title));

	clicked().connect([this](){
		this->clicked_.emit(this->obj_);
	});
}

template<typename T>
Wt::Signal<T>* ItemW<T>::item_clicked() {
	return &clicked_;
}

