#pragma once

#include <memory>

template <typename T>
class IDeferred {
public:
	virtual std::unique_ptr<T> get() = 0;
	virtual void set(std::unique_ptr<T>) = 0;

};

