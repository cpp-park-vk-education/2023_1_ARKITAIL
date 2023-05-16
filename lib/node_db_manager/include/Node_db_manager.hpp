#pragma once

#include "Main_model.hpp"

struct Ret_Tag {
  std::string name;
};

struct Ret_Node {
  int parent_id;
  Type type;
  int resource_id;
};

class node_manager {
public:
  int addNode(Ret_Node &);
  void removeNode(const int id);
  void upgradeNode(Ret_Node &);
  Ret_Node getNode(const int id);

  void addTag(const int id, Ret_Tag &);
  void move(const int id, const int destination_id);
  void subscribe(const int id, const int destination_id);
  void unsubscribe(const int id);
  std::vector<Ret_Node> getChildren(const int id);

private:
  int id;
  int destination_id;
  dbo::Session &session_;
};