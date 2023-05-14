#pragma once

#include <vector>

#include "UnmetDeps.hpp"
#include "INodeManager.hpp"
#include "Node.hpp"

class NodeManager : public INodeManager {
public:
	const Node& get(size_t node_id) override;
	void add(const Node& node) override;
	void update(const Node& node) override;
	void remove(size_t node_id) override;

	void move(size_t node_id, size_t destination_id) override;
	void subscribe(size_t node_id) override;

private:
	INodeDbManager* node_mg_;
	IDirectoryDbManager* dir_mg_;
	ICalendarDbManager* cal_mg_;
	IUserDbManager* user_mg_;
};

