#pragma once

#include <vector>

#include "Tag.hpp"
#include "Node.hpp"

class INodeManager {
public:
<<<<<<< HEAD
	virtual Node get(size_t node_id) = 0;
	virtual size_t add(const Node& node) = 0;
=======
	virtual const Node& get(int node_id) = 0;
	virtual int add(const Node& node) = 0;
>>>>>>> origin/impl-lukyanov
	virtual void update(const Node& node) = 0;
	virtual void remove(int node_id) = 0;

<<<<<<< HEAD
	virtual void tag(const Tag& tag, size_t node_id) = 0;
	virtual void move(size_t node_id, size_t destination_id) = 0;
	virtual void subscribe(size_t node_id) = 0;
	virtual void unsubscribe(size_t node_id) = 0;
	virtual std::vector<Node> getChildren(size_t node_id) = 0;
	
	virtual bool subscribed(size_t node_id) = 0;
=======
	virtual void tag(const Tag& tag, int node_id) = 0;
	virtual void move(int node_id, int destination_id) = 0;
	virtual void subscribe(int node_id) = 0;
	virtual void unsubscribe(int node_id) = 0;
	virtual std::vector<Node> getChildren(int node_id) = 0;
>>>>>>> origin/impl-lukyanov

};

