#pragma once

#include <string>
#include <vector>

#include <Wt/WDateTime.h>
#include <Wt/WDate.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/WtSqlTraits.h>
#include <Wt/Dbo/Field.h>
#include <Wt/Dbo/collection.h>
#include <Wt/Dbo/ptr.h>

#include "Node.hpp"

namespace db {
class Calendar;
class Comment;
class Directory;
class Event;
class Node;
class Profile;
class Tag;
class User;

std::vector<unsigned char> ReadFile(const std::string &filename);

using CalendarPtr = Wt::Dbo::ptr<Calendar>;
using CommentPtr = Wt::Dbo::ptr<Comment>;
using DirectoryPtr = Wt::Dbo::ptr<Directory>;
using EventPtr = Wt::Dbo::ptr<Event>;
using NodePtr = Wt::Dbo::ptr<Node>;
using ProfilePtr = Wt::Dbo::ptr<Profile>;
using TagPtr = Wt::Dbo::ptr<Tag>;
using UserPtr = Wt::Dbo::ptr<User>;

class Calendar {
public:
  Wt::Dbo::collection<EventPtr> events;
  UserPtr user; // owner
  NodePtr node;
  std::string summary;
  std::string description;
  std::string visibility;
  std::string color;

  template <class Action> void persist(Action &a) {
    Wt::Dbo::hasMany(a, events, Wt::Dbo::ManyToOne, "calendar");
    Wt::Dbo::belongsTo(a, user, "User");
    Wt::Dbo::belongsTo(a, node, "node");
    Wt::Dbo::field(a, summary, "summary");
    Wt::Dbo::field(a, description, "description");
    Wt::Dbo::field(a, color, "color");
    Wt::Dbo::field(a, visibility, "visibility");
  }
};

class Comment {
public:
  std::string text;
  Wt::Dbo::ptr<Event> event;

  template <class Action> void persist(Action &a) {
    Wt::Dbo::field(a, text, "text");
    Wt::Dbo::belongsTo(a, event, "event");
  }
};

class Profile {
public:
  std::string name;
  NodePtr node;

  template <class Action> void persist(Action &a) {
    Wt::Dbo::field(a, name, "name");
    Wt::Dbo::belongsTo(a, node, "node");
  }
};

class Directory {
public:
  UserPtr user; // owner
  NodePtr node;
  std::string name;
  std::string description;

  template <class Action> void persist(Action &a) {
    Wt::Dbo::field(a, name, "name");
    Wt::Dbo::belongsTo(a, node, "node");
    Wt::Dbo::belongsTo(a, user, "User");
    Wt::Dbo::field(a, description, "description");
  }
};

class Event {
public:
  CalendarPtr calendar;
  std::string summary;
  std::string description;
  std::string location;
  Wt::WDateTime start;
  Wt::WDateTime end;
  Wt::WDateTime stamp; // дата и временя создания события
  std::string frequency;
  int interval;
  Wt::WDate until;

  template <class Action> void persist(Action &a) {
    Wt::Dbo::belongsTo(a, calendar, "calendar");
    Wt::Dbo::field(a, summary, "summary");
    Wt::Dbo::field(a, description, "description");
    Wt::Dbo::field(a, location, "location");
    Wt::Dbo::field(a, start, "start");
    Wt::Dbo::field(a, end, "end");
    Wt::Dbo::field(a, stamp, "stamp");
    Wt::Dbo::field(a, frequency, "frequency");
    Wt::Dbo::field(a, interval, "interval");
    Wt::Dbo::field(a, until, "until");
  }
};

class Node {
public:
  NodeType type;
  NodePtr parent;
  Wt::Dbo::collection<TagPtr> tags;
  int resource_id;

  template <class Action> void persist(Action &a) {
    Wt::Dbo::field(a, type, "type");
    Wt::Dbo::belongsTo(a, parent, "parent");
    Wt::Dbo::hasMany(a, tags, Wt::Dbo::ManyToMany, "node_tags");
    Wt::Dbo::field(a, resource_id, "resource_id");
  }
};

class Tag {
public:
  std::string name;
  Wt::Dbo::collection<NodePtr> nodes;

  template <class Action> void persist(Action &a) {
    Wt::Dbo::field(a, name, "name");
    Wt::Dbo::hasMany(a, nodes, Wt::Dbo::ManyToMany, "node_tags");
  }
};

class User {
public:
  int root_id;
  std::string login;
  std::string email;
  std::string nickname;
  std::string description;
  std::string password;
  std::vector<unsigned char> avatar;
  Wt::Dbo::collection<CalendarPtr> calendars;

  template <class Action> void persist(Action &a) {
    Wt::Dbo::field(a, login, "login");
    Wt::Dbo::field(a, email, "email");
    Wt::Dbo::field(a, nickname, "nickname");
    Wt::Dbo::field(a, description, "description");
    Wt::Dbo::field(a, password, "password");
    Wt::Dbo::field(a, avatar, "avatar");
    Wt::Dbo::hasMany(a, calendars, Wt::Dbo::ManyToOne, "User");
  }
};
} // namespace db
