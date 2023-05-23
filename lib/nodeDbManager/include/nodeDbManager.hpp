#pragma once

#include "mainModel.hpp"

struct RetTag {
  int tag_id;
  std::string name;
};

struct RetNode {
  int node_id;
  int parent_id;
  NodeType type;
  int resource_id;
};

class NodeManager {
public:
  NodeManager(dbo::Session &session) : session_(session) {}

  int Add(RetNode &);
  void Remove(int id);
  void Update(RetNode &);
  RetNode Get(int id);

  void Tag(int id, RetTag &);
  void Move(int id, const int destination_id);
  std::vector<RetNode> GetChildren(int id);

private:
  int id_;
  int destination_id_;
  dbo::Session &session_;
};