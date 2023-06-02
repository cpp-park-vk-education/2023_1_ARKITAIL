#pragma once

#include <Wt/WContainerWidget.h>

#include <algorithm>
#include <memory>
#include <vector>

#include "ItemW.hpp"

template <typename T>
class ItemsContainerW : public Wt::WContainerWidget {
  public:
    ItemsContainerW();

    void addItem(std::unique_ptr<ItemW<T>> item);
    void removeItem(ItemW<T>* item);
    bool hasItem(const std::string title);

  private:
    std::vector<ItemW<T>*> items_;
};

template <typename T>
ItemsContainerW<T>::ItemsContainerW() {}

template <typename T>
void ItemsContainerW<T>::addItem(std::unique_ptr<ItemW<T>> item) {
    items_.push_back(addWidget(std::move(item)));
}

template <typename T>
void ItemsContainerW<T>::removeItem(ItemW<T>* item) {
    for (auto i = items_.begin(); i != items_.end(); i++)
        if (*i == item) {
            removeItem(*i);
            items_.erase(i);
            break;
        };
}

template <typename T>
bool ItemsContainerW<T>::hasItem(const std::string title) {
    for (auto i = items_.begin(); i != items_.end(); i++) {
        if ((*i)->getTitle() == title) {
			std::cout << "\n True \n";
            return true;
        }
    }
    return false;
}
