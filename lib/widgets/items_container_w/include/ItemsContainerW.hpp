#pragma once

#include <Wt/WContainerWidget.h>
#include <memory>
#include <vector>

#include "ItemW.hpp"

template<typename T>
class ItemsContainerW : public Wt::WContainerWidget {
public: 
	void addItem(std::unique_ptr<ItemW<T>> item);
	void deleteItem(ItemW<T>* item);

private:
	std::vector<ItemW<T>*> items_;

};

