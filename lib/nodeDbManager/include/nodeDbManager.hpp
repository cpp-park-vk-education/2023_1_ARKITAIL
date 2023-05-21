#pragma once

#include "mainModel.hpp"

struct Ret_Tag {
  int tag_id;
  std::string name;
  std::vector<int> node_id;
};

struct Ret_Node {
  int parent_id;
  Type type;
  int resource_id;
  std::vector<int> tag_id;
};

class NodeManager {
public:
  int add(Ret_Node &);
  void remove(const int id);
  void update(Ret_Node &);
  Ret_Node get(const int id);

  void tag(const int id, Ret_Tag &);
  void move(const int id, const int destination_id);
  std::vector<Ret_Node> getChildren(const int id);

private:
  int id;
  int destination_id;
  dbo::Session &session_;
};