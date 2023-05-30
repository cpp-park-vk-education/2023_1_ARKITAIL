#pragma once

#include "ItemW.hpp"

template<typename T>
class RemovableItemW : public ItemW<T> {
public:
	RemovableItemW(const T& obj);

};

