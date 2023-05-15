#pragma once

#include <vector>

#include "Node.hpp"

class INodeManager {
public:
	virtual const Node& get(size_t node_id) = 0;
	virtual size_t add(const Node& node) = 0;
	virtual void update(const Node& node) = 0;
	virtual void remove(size_t node_id) = 0;

	virtual void move(size_t node_id, size_t destination_id) = 0;
	virtual void subscribe(size_t node_id) = 0;
	virtual void unsubscribe(size_t node_id) = 0;

};
