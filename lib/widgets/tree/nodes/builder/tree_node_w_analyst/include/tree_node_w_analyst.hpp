#pragma once

#include <memory>
#include <vector>

#include "ITreeNode.hpp"
#include "Tag.hpp"

// |1| |2| |3'4'5'6'7| |8| |9'10|

// 1) checkBox
// 0 - нет
// 1 - есть

// 2) label
// 0 - просто текстом название,
// 1 - редактируемое поле

// 3,4,5,6,7) options
// 00000 - none,
// 00001 - unsub,
// 00010 - sub,
// 00100 -calendars_dir,
// 01000 - personal_calendar,
// 10000 - profile

// 8) tooltip
// 0 - нет
// 1 - есть

// 9,10) type node
// 00 - leaf
// 01 - other dir
// 10 - sub dir
// 11 - dir

enum TreeNodeWType {
    GROUP,  // большая часть групп
    DIR,    // свои директории

    SUB_GROUP,  // группа подписок
    SUB_DIR,  // директория из подписок без возможности отписаться(не mount)
    SUB_DIR_OPTIONS,  // директория из подписок с возможностью отписаться

    OTHER_GROUP_SUB,  // группа в чужом профиле, на которую можно подписаться
    OTHER_GROUP_UNSUB,  // группа в чужом профиле, от которой можно отписаться
    OTHER_DIR_SUB,  // директория в чужом профиле, на которую можно подписаться
    OTHER_DIR_UNSUB,  // директория в чужом профиле, от которой можно отписаться

    PROFILE_LEAF,        // профиль
    PERSONAL_CALENDAR,   // свой календарь
    OTHER_SUB_CALENDAR,  // календарь в чужом профиле, на который можно подписаться
    OTHER_UNSUB_CALENDAR,  // календарь в чужом профиле, от которого можно отписаться
    SUB_CALENDAR,  // календарь из подписок без возможности отписаться(не mount)
    SUB_CALENDAR_OPTIONS,  // календарь из подписок с возможностью отписаться
};

struct TreeNodeWConvertedData {
    TreeNodeWType components_set;
    std::string name;
    std::string description;
    std::vector<Tag> tags;
    std::string user_nickname;
};

class TreeNodeWAnalyst {
  public:
    TreeNodeWAnalyst();
    ~TreeNodeWAnalyst() = default;

    TreeNodeWConvertedData analyseTreeNodeDirWChild(ITreeNode* tree_node);
    TreeNodeWConvertedData analyseTreeNodeOtherDirWChild(ITreeNode* tree_node);
    TreeNodeWConvertedData analyseTreeNodeSubscriptionDirWChild(ITreeNode* tree_node);
};
