#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WSignal.h>
#include <Wt/WText.h>

template<typename T>
class ItemW : public Wt::WPushButton {
public:
	ItemW(const T& obj);
	Wt::Signal<T>* clicked();

protected:
	Wt::Signal<T> clicked_;
	T obj_;

};

template<typename T>
ItemW<T>::ItemW(const T& obj) :
	clicked_(),
	obj_(obj) {

	clicked()->connect([&](){
		clicked_.emit(obj);
	});
}

template<typename T>
Wt::Signal<T>* ItemW<T>::clicked() {
	return &clicked_;
}

