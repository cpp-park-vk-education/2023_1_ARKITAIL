#pragma once

#include "baseForAll.hpp"

class users;
class calendars;
class events;
class nodes;
class directory;
class tags;
class profiles;
class comments;

class calendars {
public:
  //dbo::ptr<users> user; // Owner
  std::string name;     // name
  std::string description;
  dbo::collection<dbo::ptr<events>> event; // event
  //dbo::ptr<nodes> node;                    // p_node

  template <class Action> void persist(Action &a) {
    dbo::field(a, name, "name");
    dbo::hasMany(a, event, dbo::ManyToOne, "calendar");
    dbo::field(a, description, "description");
    //dbo::belongsTo(a, user, "user");
    //dbo::belongsTo(a, node, "node");
  }
};

class profiles {
public:
  std::string name;
  dbo::ptr<nodes> node;

  template <class Action> void persist(Action &a) {
    dbo::field(a, name, "name");
    dbo::belongsTo(a, node, "node");
  }
};

class comments {
public:
  std::string name;
  std::string text;
  dbo::ptr<events> event;

  template <class Action> void persist(Action &a) {
    dbo::field(a, name, "name");
    dbo::field(a, text, "text");
    dbo::belongsTo(a, event, "event");
  }
};

class directory {
public:
  std::string name;
  std::string description;
  dbo::ptr<nodes> node;

  template <class Action> void persist(Action &a) {
    dbo::field(a, name, "name");
    dbo::field(a, description, "description");
    dbo::belongsTo(a, node, "node");
  }
};

class events {
public:
  std::string name;
  std::time_t time_start;
  std::time_t time_end;
  std::string description;
  dbo::ptr<calendars> calendar;
  dbo::collection<dbo::ptr<comments>> comment;

  template <class Action> void persist(Action &a) {
    dbo::field(a, name, "name");
    dbo::field(a, time_start, "time_start");
    dbo::field(a, time_end, "time_end");
    dbo::field(a, description, "description");
    dbo::belongsTo(a, calendar, "calendar");
  }
};

enum class Type {
  Root = 0,
  Private_Group = 1,
  Private_Directory = 2,
  Private_Calendar = 3,
  Public_Group = 4,
  Public_Directory = 5,
  Public_Calendar = 6,
  Subscription_Group = 7,
  Mount = 8,
  Profile_Group = 9,
  Profile = 10
};

class nodes {
public:
  Type type;
  dbo::ptr<nodes> parent;
  dbo::collection<dbo::ptr<tags>> tag;
  int resource_id;

  template <class Action> void persist(Action &a) {
    dbo::field(a, type, "type");
    dbo::belongsTo(a, parent, "parent");
    dbo::hasMany(a, tag, dbo::ManyToMany, "node_tags");
    dbo::field(a, resource_id, "resource_id");
  }
};

class tags {
public:
  std::string name;
  dbo::collection<dbo::ptr<nodes>> node;

  template <class Action> void persist(Action &a) {
    dbo::field(a, name, "name");
    dbo::hasMany(a, node, dbo::ManyToMany, "node_tags");
  }
};

std::vector<unsigned char> read_file(const std::string &filename) {
  std::ifstream file(filename, std::ios::binary);
  return std::vector<unsigned char>(std::istreambuf_iterator<char>(file),
                                    std::istreambuf_iterator<char>());
}

class users;
using AuthInfo = Wt::Auth::Dbo::AuthInfo<users>;

class users {
public:
  int root_id;
  std::string login;
  std::string email;
  std::string nickname;
  std::string description;
  std::string password;
  std::vector<unsigned char> avatar;
  dbo::collection<dbo::ptr<calendars>> calendar;

  template <class Action> void persist(Action &a) {
    dbo::field(a, login, "login");
    dbo::field(a, email, "email");
    dbo::field(a, nickname, "nickname");
    dbo::field(a, description, "description");
    dbo::field(a, password, "password");
    dbo::field(a, avatar, "avatar");
    dbo::hasMany(a, calendar, dbo::ManyToOne, "user");
  }
};

DBO_EXTERN_TEMPLATES(users)