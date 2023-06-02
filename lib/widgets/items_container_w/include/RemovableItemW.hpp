#pragma once

#include "ItemW.hpp"
#include <Wt/WPushButton.h>
#include <Wt/WSignal.h>

template<typename T>
class RemovableItemW : public ItemW<T> {
public:
	RemovableItemW(const std::string& title, const T& obj);

};

template<typename T>
RemovableItemW<T>::RemovableItemW(const std::string& title, const T& obj) :
	ItemW<T>(title, obj) {
	ItemW<T>::addStyleClass("mt-2 me-2");
	ItemW<T>::clicked().connect([this](){
	 	this->ItemW<T>::clicked_.emit(this->ItemW<T>::obj_);
	 	this->ItemW<T>::parent()->removeChild(this);
	});
}

