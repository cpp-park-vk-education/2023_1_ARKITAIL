#pragma once

#include <Wt/WWidget.h>
#include <memory>

template<typename T>
class Swapable {
public:
	Swapable();
	Swapable(std::unique_ptr<T> content);
	
	void swap();

	void set_destination(Swapable* destination);
	void build_destination();

	void set_content(std::unique_ptr<T> content);
	T* get_content();

private:
	Swapable* destination_;
	std::unique_ptr<T> content_;

};


template<typename T>
Swapable<T>::Swapable() :
	destination_(nullptr),
	content_() {}

template<typename T>
Swapable<T>::Swapable(std::unique_ptr<T> content) :
	Swapable() {

	content_.swap(content);
}

template<typename T>
void Swapable<T>::swap() {
	content_.swap(destination_->content_);
}

template<typename T>
void Swapable<T>::set_destination(Swapable* destination) {
	destination_ = destination;
}

template<typename T>
void Swapable<T>::build_destination() {
	destination_->destination_ = this;
}

template<typename T>
void Swapable<T>::set_content(std::unique_ptr<T> content) {
	content_.swap(content);
}

template<typename T>
T* Swapable<T>::get_content() {
	return content_.get();
}

