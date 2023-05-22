#include <queue>
#include <vector>
#include <memory>

#include "DbManagers.hpp"
#include "IDbManagers.hpp"
#include "Managers.hpp"
#include "NodeManager.hpp"
#include "Node.hpp"

NodeManager::NodeManager(std::shared_ptr<IDbManagers> db) :
	db_(db) {}

// TODO(uma_op): Проверку доступа можно осуществить, получением связанного ресурса
// и сравнения айди текущего пользователя и владельца ресурса
const Node& NodeManager::get(int node_id) {
	return db_->node_dbm()->get(node_id);
}

// TODO(uma_op): Проверка типа добавляемой директории
// В ноду типа PRIVATE_{GROUP | DIRECTORY}
// можно добавить только PRIVATE_{DIRECTORY | CALENDAR}
// Аналогично и для PUBLIC
// В ноду типа SUBSCRIPTIONS_GROUP
// можно добавить только MOUNT
// В ноды ROOT, MOUNT, PUBLIC_CALENDAR, PRIVATE_CALENDAR добавить ничего нельзя
int NodeManager::add(const Node& node) {
	return db_->node_dbm()->add(node);
}

// TODO(uma_op): Проверка соответствия типов аналогичная добавлению
// можно менять только поле parent_id
void NodeManager::update(const Node& node) {
	db_->node_dbm()->update(node);
}

// TODO(uma_op): Удалять запрещено типы ROOT, {PRIVATE | PUBLIC | SUBSCRIPTIONS | PROFILE}_GROUP
void NodeManager::remove(int node_id) {
	const Node& node = db_->node_dbm()->get(node_id);

	std::queue<Node> subtree;
	subtree.push(node);

	Node cur_node;

	while (!subtree.empty()) {
		cur_node = subtree.front();

		if (cur_node.type & (NodeType::PRIVATE_DIRECTORY | NodeType::PUBLIC_DIRECTORY))
			for (auto child_node : db_->node_dbm()->getChildren(cur_node.id))
				subtree.push(child_node);

		db_->node_dbm()->remove(cur_node.id);
		
		if (cur_node.type & (NodeType::PRIVATE_DIRECTORY | NodeType::PUBLIC_DIRECTORY))
			db_->directory_dbm()->remove(cur_node.resource_id);
		else if (cur_node.type & (NodeType::PRIVATE_CALENDAR | NodeType::PUBLIC_CALENDAR))
			db_->calendar_dbm()->remove(cur_node.resource_id);
        
		subtree.pop();
	}
}

void NodeManager::tag(const Tag& tag, int node_id) {
	// TODO(uma_op): IMPLEMENT ME
}

// TODO(uma_op): Проверка соответствию типов
// Проверка на то, что перемещение осуществляется только внутри дерева одного пользователя
// и в ноды с валидными типами
void NodeManager::move(int node_id, int destination_id) {
	const Node& mv_node = db_->node_dbm()->get(node_id); 
	Node mvd_node = mv_node;
	mvd_node.parent_id = destination_id;
}

// TODO(uma_op): Проверка на права доступа
// Подписка может осуществиться только на PUBLIC_{DIRECTORY | CALENDAR}
void NodeManager::subscribe(int node_id) {
	const User& user = db_->user_dbm()->get();

	for (auto subg : db_->node_dbm()->getChildren(user.root_id)) {
		if (subg.type & NodeType::SUBSCRIPTIONS_GROUP) {
			Node mount_node = {
				0,
				subg.id,
				node_id,
				NodeType::MOUNT
			};
				
			db_->node_dbm()->add(mount_node);

			break;
		}
	}
}

// Отписка является одной из самых безобидных операций
// и не требует никаких проверок
void NodeManager::unsubscribe(int node_id) {
	const User& user = db_->user_dbm()->get();

	for (auto subg : db_->node_dbm()->getChildren(user.root_id))
		if (subg.type & NodeType::SUBSCRIPTIONS_GROUP) {
			for (auto sub : db_->node_dbm()->getChildren(subg.id))
				if (sub.resource_id == node_id) {
					db_->node_dbm()->remove(sub.id);
					break;
				}

			break;
		}
}

// TODO(uma_op) Получение детей так же как и получение требует лишь проверки прав доступа
std::vector<Node> NodeManager::getChildren(int node_id) {
	return db_->node_dbm()->getChildren(node_id);
}

