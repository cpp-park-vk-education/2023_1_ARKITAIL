#pragma once

#include "PageWidget.hpp"
#include <memory>

class Swapable {
public:
	Swapable();
	Swapable(std::unique_ptr<PageWidget> content);
	
	void swap();

	void set_destination(Swapable* destination);
	void build_destination();

private:
	Swapable* destination_;
	std::unique_ptr<PageWidget> content_;

};

