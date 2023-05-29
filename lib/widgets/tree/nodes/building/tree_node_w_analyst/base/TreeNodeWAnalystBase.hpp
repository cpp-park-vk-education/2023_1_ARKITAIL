#pragma once

#include "IManagers.hpp"
#include "ITreeNode.hpp"
#include "User.hpp"
#include "Tag.hpp"

// |1| |2| |3| |4'5'6'7'8| |9'10'11|

// 1) checkBox
// 0 - нет
// 1 - есть

// 2) label
// 0 - просто текстом название,
// 1 - редактируемое поле

// 3) tooltip
// 0 - нет автора
// 1 - есть автор

// 4,5,6,7,8) options
// 00000 - none,
// 00001 - unsub,
// 00010 - sub,
// 00100 -calendars_dir,
// 01000 - personal_calendar,
// 10000 - profile

// 9,10,11) type node
// 000 - leaf
// 001 - other dir
// 010 - sub dir
// 100 - dir

enum Components {
    TYPE_LEAF = 1,
    TYPE_SUB_DIR = 1 << 1,
    TYPE_OTHER_DIR = 1 << 2,

    OPTIONS_UNSUB = 1 << 3,
    OPTIONS_SUB = 1 << 4,
    OPTIONS_CALENDARS_DIR = 1 << 5,
    OPTIONS_PERSONAL_CALENDAR = 1 << 6,
    OPTIONS_PROFILE = 1 << 7,

    TOOLTIP_AUTHOR = 1 << 8,

    LABEL = 1 << 9,

    CHECKBOX = 1 << 10,
};

enum TreeNodeWType {
    GROUP,                                                           // группы
    DIR = Components::CHECKBOX | Components::OPTIONS_CALENDARS_DIR,  // свои директории

    SUB_GROUP = Components::TYPE_SUB_DIR,  // группа подписок
    SUB_DIR =
        Components::CHECKBOX | Components::TOOLTIP_AUTHOR |
        Components::TYPE_SUB_DIR,  // директория из подписок без возможности отписаться(не mount)
    SUB_DIR_OPTIONS =
        Components::CHECKBOX | Components::TOOLTIP_AUTHOR | Components::TYPE_SUB_DIR |
        Components::OPTIONS_UNSUB,  // директория из подписок с возможностью отписаться

    OTHER_GROUP_SUB = Components::CHECKBOX | Components::OPTIONS_SUB |
                      TYPE_OTHER_DIR,  // группа в чужом профиле, на которую можно подписаться
    OTHER_GROUP_UNSUB = Components::CHECKBOX | Components::OPTIONS_UNSUB |
                        TYPE_OTHER_DIR,  // группа в чужом профиле, от которой можно отписаться
    OTHER_DIR_SUB = Components::CHECKBOX | Components::OPTIONS_SUB |
                    TYPE_OTHER_DIR,  // директория в чужом профиле, на которую можно подписаться
    OTHER_DIR_UNSUB = Components::CHECKBOX | Components::OPTIONS_UNSUB |
                      TYPE_OTHER_DIR,  // директория в чужом профиле, от которой можно отписаться

    PROFILE_LEAF = Components::TYPE_LEAF | Components::CHECKBOX | Components::LABEL |
                   Components::OPTIONS_PROFILE,  // профиль
    PERSONAL_CALENDAR = Components::TYPE_LEAF | Components::CHECKBOX |
                        Components::OPTIONS_PERSONAL_CALENDAR,  // свой календарь
    OTHER_CALENDAR_SUB =
        Components::TYPE_LEAF | Components::CHECKBOX |
        Components::OPTIONS_SUB,  // календарь в чужом профиле, на который можно подписаться
    OTHER_CALENDAR_UNSUB =
        Components::TYPE_LEAF | Components::CHECKBOX |
        Components::OPTIONS_UNSUB,  // календарь в чужом профиле, от которого можно отписаться
    SUB_CALENDAR =
        Components::TYPE_LEAF | Components::CHECKBOX |
        Components::TOOLTIP_AUTHOR,  // календарь из подписок без возможности отписаться(не mount)
    SUB_CALENDAR_OPTIONS =
        Components::TYPE_LEAF | Components::CHECKBOX | Components::TOOLTIP_AUTHOR |
        Components::OPTIONS_UNSUB,  // календарь из подписок с возможностью отписаться
};

struct TreeNodeWConvertedData {
    TreeNodeWType components_set;
    std::string name;
    std::string description;
    std::vector<Tag> tags;
    User author;
    ITreeNode* tree_node;
};

class TreeNodeWAnalystBase {
  protected:
    IManagers* managers_;

  public:
    TreeNodeWAnalystBase() {}
    TreeNodeWAnalystBase(IManagers* managers) :
        managers_(managers) {}
    virtual ~TreeNodeWAnalystBase() {}

    virtual TreeNodeWConvertedData analyseTreeNodeWChild(ITreeNode* tree_node) = 0;
};
