#pragma once

#include "Node.hpp"
#include "baseForAll.hpp"

class Users;
class Calendars;
class Events;
class Nodes;
class Directories;
class Tags;
class Profiles;
class Comments;

class Calendars {
public:
  dbo::ptr<Users> user; // Owner
  std::string name;     // name
  std::string description;
  dbo::collection<dbo::ptr<Events>> event; // event
  dbo::ptr<Nodes> node;                    // p_node

  template <class Action> void persist(Action &a) {
    dbo::field(a, name, "name");
    dbo::hasMany(a, event, dbo::ManyToOne, "calendar");
    dbo::field(a, description, "description");
    dbo::belongsTo(a, user, "User");
    dbo::belongsTo(a, node, "node");
  }
};

class Profiles {
public:
  dbo::ptr<Users> user;
  dbo::ptr<Nodes> node;
  //std::vector<int> nodes_id;


  template <class Action> void persist(Action &a) {
    dbo::belongsTo(a, user, "User");
    dbo::belongsTo(a, node, "node");
    //dbo::field(a, nodes_id, "nodes_id");

  }
};

class Comments {
public:
  std::string text;
  dbo::ptr<Events> event;

  template <class Action> void persist(Action &a) {
    dbo::field(a, text, "text");
    dbo::belongsTo(a, event, "event");
  }
};

class Directories {
public:
  dbo::ptr<Users> user; // Owner
  std::string name;
  std::string description;
  dbo::ptr<Nodes> node;

  template <class Action> void persist(Action &a) {
    dbo::field(a, name, "name");
    dbo::belongsTo(a, user, "User");
    dbo::field(a, description, "description");
    dbo::belongsTo(a, node, "node");
  }
};

class Events {
public:
  std::string name;
  Wt::WDateTime time_start;
  Wt::WDateTime time_end;
  std::string description;
  dbo::ptr<Calendars> calendar;
  dbo::collection<dbo::ptr<Comments>> comment;

  template <class Action> void persist(Action &a) {
    dbo::field(a, name, "name");
    dbo::field(a, time_start, "time_start");
    dbo::field(a, time_end, "time_end");
    dbo::field(a, description, "description");
    dbo::belongsTo(a, calendar, "calendar");
  }
};

class Nodes {
public:
  NodeType type;
  dbo::ptr<Nodes> parent;
  dbo::collection<dbo::ptr<Tags>> tag;
  int resource_id;

  template <class Action> void persist(Action &a) {
    dbo::field(a, type, "type");
    dbo::belongsTo(a, parent, "parent");
    dbo::hasMany(a, tag, dbo::ManyToMany, "NodeTags");
    dbo::field(a, resource_id, "resource_id");
  }
};

class Tags {
public:
  std::string name;
  dbo::collection<dbo::ptr<Nodes>> node;

  template <class Action> void persist(Action &a) {
    dbo::field(a, name, "name");
    dbo::hasMany(a, node, dbo::ManyToMany, "NodeTags");
  }
};

std::vector<unsigned char> read_file(const std::string &filename) {
  std::ifstream file(filename, std::ios::binary);
  return std::vector<unsigned char>(std::istreambuf_iterator<char>(file),
                                    std::istreambuf_iterator<char>());
}

class Users {
public:
  int root_id;
  std::string login;
  std::string email;
  std::string nickname;
  std::string description;
  std::string password;
  std::vector<unsigned char> avatar;
  dbo::collection<dbo::ptr<Calendars>> calendar;

  template <class Action> void persist(Action &a) {
    dbo::field(a, login, "login");
    dbo::field(a, email, "email");
    dbo::field(a, nickname, "nickname");
    dbo::field(a, description, "description");
    dbo::field(a, password, "password");
    dbo::field(a, avatar, "avatar");
    dbo::hasMany(a, calendar, dbo::ManyToOne, "User");
  }
};