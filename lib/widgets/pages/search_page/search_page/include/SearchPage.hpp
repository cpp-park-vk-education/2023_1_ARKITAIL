#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

#include "Searcher.hpp"
#include "CalendarCardContainerW.hpp"
#include "UsersLineEdit.hpp"
#include "TagsLineEdit.hpp"

class SearchP : public Wt::WContainerWidget {
public:
    SearchP();
    void search();
       
private:
    UsersLineEdit* users_;
    TagsLineEdit* tags_;
    
    Wt::WText* hint_;
    CalendarCardContainerW* found_;
    Searcher* searcher_;

};

