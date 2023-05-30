#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WSignal.h>
#include <Wt/WText.h>

template<typename T>
class ItemW : public Wt::WPushButton {
public:
	ItemW(const T& obj);

private:
	Wt::Signal<T> clicked_;
	T obj_;

};

