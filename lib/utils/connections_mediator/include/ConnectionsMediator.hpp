#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WSignal.h>

#include "ConnectionPoint.hpp"
#include "Event.hpp"
#include "ICalendarBodyW.hpp"
#include "ITreeNode.hpp"
#include "SearchPage.hpp"
#include "TreeW.hpp"
#include "Wt/WDate.h"
#include "i_calendar_header_w.hpp"
#include "Profile.hpp"
#include "User.hpp"
#include "OtherUserP.hpp"

class ConnectionsMediator {
  public:
    ConnectionsMediator();

    void connect();

    // Declare your connetion points there
    ConnectionPoint<Wt::Signal<int>, Wt::WContainerWidget, int> cp;

    // сигналы от нод к дереву при нажатии чекбокса
    ConnectionPoint<Wt::Signal<ITreeNode*>, TreeW, ITreeNode*> node_to_tree_main;
    ConnectionPoint<Wt::Signal<ITreeNode*>, TreeW, ITreeNode*> node_to_tree_other;

    // сигналы от дерева хедеру календаря передаются при чеке ноды, ничего не несет
    ConnectionPoint<Wt::Signal<>, ICalendarHeaderW> tree_to_header_main;
    ConnectionPoint<Wt::Signal<>, ICalendarHeaderW> tree_to_header_other;

    // сигналы от дерева телу календаря, передается первая дата и события нужного промежутка
    // промежуток для календаря передается отдельно сразу от хедера телу - делается обычным сигналом
    ConnectionPoint<Wt::Signal<Wt::WDate, std::vector<Event>>, ICalendarBodyW, Wt::WDate,
                    std::vector<Event>>
        tree_to_body_main;
    ConnectionPoint<Wt::Signal<Wt::WDate, std::vector<Event>>, ICalendarBodyW, Wt::WDate,
                    std::vector<Event>>
        tree_to_body_other;

    // сигналы от хедера дереву, несут начальную и конечную дату календарной сетки
    // в случае одного дня - это две одинаковые даты
    ConnectionPoint<Wt::Signal<Wt::WDate, Wt::WDate>, TreeW, Wt::WDate, Wt::WDate>
        header_to_tree_main;
    ConnectionPoint<Wt::Signal<Wt::WDate, Wt::WDate>, TreeW, Wt::WDate, Wt::WDate>
        header_to_tree_other;

    // сигнал для передачи ноды из поиска при клике на календарь в дерево
    ConnectionPoint<Wt::Signal<const Node&>, TreeW, const Node&> set_tree_root;

    // сигнал для передачи тега на страницу поиска
    ConnectionPoint<Wt::Signal<Tag>, TagsLineEdit, const Tag&> search_tag;

    // сигнал для перехода на чужой профиль
    ConnectionPoint<Wt::Signal<User>, OtherUserP, const User&> swap_to_profile_page;
};
