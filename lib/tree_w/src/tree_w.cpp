#include "tree_w.hpp"

#include <Wt/WContainerWidget.h>

#include <memory>

TreeW::TreeW() { search_line_ = addWidget(std::make_unique<Wt::WLineEdit>()); }