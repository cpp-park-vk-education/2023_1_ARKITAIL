#pragma once

#include "mainModel.hpp"

struct RetTag {
  int tag_id;
  std::string name;
  std::vector<int> node_id;
};

struct RetNode {
  int node_id;
  int parent_id;
  Type type;
  int resource_id;
  std::vector<int> tag_id;
};

class NodeManager {
public:
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