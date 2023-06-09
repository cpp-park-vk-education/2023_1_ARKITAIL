#pragma once

#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

#include "PageW.hpp"
#include "Searcher.hpp"
#include "CalendarCardContainerW.hpp"

class SearchP : PageW {
public:
    void SearchP();
    void Find(std::string input_string);
       
private:
    Wt::WLineEdit* input_users_;
    Wt::WLineEdit* input_tags_;
    Wt::WPushButton& find_button_;
    Wt::WText* hint_;
    CalendarCardContainerW* found_;
    Searcher* searcher_;

};

