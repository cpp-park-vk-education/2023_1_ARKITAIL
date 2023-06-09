#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WSignal.h>

#include "ConnectionPoint.hpp"
#include "Event.hpp"
#include "ICalendarBodyW.hpp"
#include "ITreeNode.hpp"
#include "TreeW.hpp"
#include "Wt/WDate.h"
#include "i_calendar_header_w.hpp"

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
};
