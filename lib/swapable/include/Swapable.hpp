#pragma once

#include "PageWidget.hpp"
#include <Wt/WWidget.h>
#include <memory>

class Swapable {
public:
	Swapable();
	Swapable(std::unique_ptr<PageWidget> content);
	
	void swap();

	void set_destination(Swapable* destination);
	void build_destination();

	void set_content(std::unique_ptr<PageWidget> content);
	std::unique_ptr<PageWidget> get_content();

private:
	Swapable* destination_;
	std::unique_ptr<PageWidget> content_;

};

