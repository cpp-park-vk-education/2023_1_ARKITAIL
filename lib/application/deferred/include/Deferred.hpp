#pragma once

#include <iostream>
#include <algorithm>
#include <memory>
#include <thread>

#include "IDeferred.hpp"

template <typename T, typename TBase = T>
class Deferred : public IDeferred<TBase> {
public:
	std::unique_ptr<TBase> get() override;
	void set(std::unique_ptr<TBase>) override;
	
private:
	std::unique_ptr<TBase> obj_;

};

template <typename T, typename TBase>
std::unique_ptr<TBase> Deferred<T, TBase>::get() {
	if (!obj_) {
		obj_ = std::make_unique<T>();
		std::cout << "This thread has id: " << std::this_thread::get_id() << std::endl;
	}

	return std::move(obj_);
}

template <typename T, typename TBase>
void Deferred<T, TBase>::set(std::unique_ptr<TBase> obj) {
	obj_.reset(obj.release());
}

