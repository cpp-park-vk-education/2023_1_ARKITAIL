#pragma once

#include "ItemW.hpp"
#include <Wt/WPushButton.h>
#include <Wt/WSignal.h>

template<typename T>
class RemovableItemW : public ItemW<T> {
public:
	RemovableItemW(const T& obj);

};

template<typename T>
RemovableItemW<T>::RemovableItemW(const T& obj) :
	ItemW<T>(obj) {
	
	ItemW<T>::clicked()->connect([&](){
		ItemW<T>::clicked_.emit(ItemW<T>::obj_);
		ItemW<T>::parent()->removeChild(this);
	});
}

