#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WSignal.h>

#include "ItemsContainerW.hpp"
#include "Tag.hpp"

class TagsLineEdit : public Wt::WContainerWidget {
public:
	TagsLineEdit();
	void appendItem(const Tag& tag);

private:
	Wt::WLineEdit* line_edit_;
	ItemsContainerW<Tag>* tags_;

	Wt::Signal<Tag> added_;
	Wt::Signal<Tag> removed_;

};

