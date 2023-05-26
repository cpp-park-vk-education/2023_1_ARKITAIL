#include "NodeManager.hpp"

#include <memory>
#include <queue>
#include <vector>

#include "Calendar.hpp"
#include "DbManagers.hpp"
#include "Directory.hpp"
#include "IDbManagers.hpp"
#include "Managers.hpp"
#include "Node.hpp"

NodeManager::NodeManager(std::shared_ptr<IDbManagers> db) :
    db_(db) {}

<<<<<<< HEAD
bool NodeManager::checkAccess(size_t user_id, size_t node_id) {
    Node node = db_->node_dbm()->get(node_id);

    if (node.type & DIRECTORY)
        return db_->directory_dbm()->get(node.resource_id).owner_id == user_id;

    if (node.type & CALENDAR)
        return db_->calendar_dbm()->get(node.resource_id)->owner_id == user_id;

    if (node.type & MOUNT) return checkAccess(user_id, node.parent_id);

    return false;
}

Node NodeManager::get(size_t node_id) {
    User user = db_->user_dbm()->get();

    // if (!checkAccess(user.id, node_id))
    // 	return Node();

    return db_->node_dbm()->get(node_id);
=======
// TODO(uma_op): Проверку доступа можно осуществить, получением связанного ресурса
// и сравнения айди текущего пользователя и владельца ресурса
const Node& NodeManager::get(int node_id) {
	return db_->node_dbm()->get(node_id);
>>>>>>> origin/impl-lukyanov
}

// В ноду типа PRIVATE_{GROUP | DIRECTORY}
// можно добавить только PRIVATE_{DIRECTORY | CALENDAR}
// Аналогично и для PUBLIC
// В ноду типа SUBSCRIPTIONS_GROUP
// можно добавить только MOUNT и наоборот
// В ноды ROOT, MOUNT, PUBLIC_CALENDAR, PRIVATE_CALENDAR добавить ничего нельзя
<<<<<<< HEAD
// Ресурсом MOUNT может быть только нодой с ресурсом PUBLIC_{DIRECTORY | CALENDAR}
size_t NodeManager::add(const Node& node) {
    User user = db_->user_dbm()->get();

    if (!checkAccess(user.id, node.parent_id)) return 0;

    if (node.type & (PRIVATE_DIRECTORY | PUBLIC_DIRECTORY)) {
        Node parent_node = db_->node_dbm()->get(node.parent_id);

        if (!(parent_node.type & PRIVATE_GD && node.type & PRIVATE_DIRECTORY ||
              parent_node.type & PUBLIC_GD && node.type & PUBLIC_DIRECTORY ||
              checkAccess(user.id, node.id)))
            return 0;

    } else if (node.type & CALENDAR) {
        Node parent_node = db_->node_dbm()->get(node.parent_id);

        if (!(parent_node.type & PRIVATE_GD && node.type & PRIVATE_CALENDAR ||
              parent_node.type & PUBLIC_GD && node.type & PUBLIC_CALENDAR ||
              checkAccess(user.id, node.id)))
            return 0;

    } else if (node.type & MOUNT) {
        Node parent_node = db_->node_dbm()->get(node.parent_id);

        if (!(parent_node.type & SUBSCRIPTIONS_GROUP)) return 0;

        Node resource_node = db_->node_dbm()->get(node.resource_id);

        if (!(resource_node.type & (PUBLIC_DIRECTORY | PUBLIC_CALENDAR))) return 0;

    } else {
        return 0;
    }

    return db_->node_dbm()->add(node);
=======
int NodeManager::add(const Node& node) {
	return db_->node_dbm()->add(node);
>>>>>>> origin/impl-lukyanov
}

// Можно менять только поле parent_id функция аналогична NodeManager::move
void NodeManager::update(const Node& node) {
    User user = db_->user_dbm()->get();
    Node prev_node = db_->node_dbm()->get(node.id);
    Node prev_parent_node = db_->node_dbm()->get(prev_node.parent_id);
    Node parent_node = db_->node_dbm()->get(node.parent_id);

    if (!checkAccess(user.id, parent_node.id) || prev_parent_node.type != parent_node.type ||
        prev_node.resource_id != node.resource_id || prev_node.type != node.type)
        return;

    db_->node_dbm()->update(node);
}

<<<<<<< HEAD
// Удалять запрещено типы ROOT, {PRIVATE | PUBLIC | SUBSCRIPTIONS | PROFILE}_GROUP
void NodeManager::remove(size_t node_id) {
	User user = db_->user_dbm()->get();
	Node node = db_->node_dbm()->get(node_id);
=======
// TODO(uma_op): Удалять запрещено типы ROOT, {PRIVATE | PUBLIC | SUBSCRIPTIONS | PROFILE}_GROUP
void NodeManager::remove(int node_id) {
	const Node& node = db_->node_dbm()->get(node_id);
>>>>>>> origin/impl-lukyanov

	if (!checkAccess(user.id, node.id) ||
		node.type & (ROOT | PRIVATE_GROUP | PUBLIC_GROUP | SUBSCRIPTIONS_GROUP | PROFILE_GROUP))
		return;

    std::queue<Node> subtree;
    subtree.push(node);

    Node cur_node;

    while (!subtree.empty()) {
        cur_node = subtree.front();

		if (cur_node.type & (PRIVATE_DIRECTORY | PUBLIC_DIRECTORY))
			for (auto child_node : db_->node_dbm()->getChildren(cur_node.id))
				subtree.push(child_node);

		db_->node_dbm()->remove(cur_node.id);
		
		if (cur_node.type & (PRIVATE_DIRECTORY | PUBLIC_DIRECTORY))
			db_->directory_dbm()->remove(cur_node.resource_id);
		else if (cur_node.type & (PRIVATE_CALENDAR | PUBLIC_CALENDAR))
			db_->calendar_dbm()->remove(cur_node.resource_id);
        
		subtree.pop();
	}
}

<<<<<<< HEAD
void NodeManager::tag(const Tag& tag, size_t node_id) {
    // TODO(uma_op): IMPLEMENT ME
=======
void NodeManager::tag(const Tag& tag, int node_id) {
	// TODO(uma_op): IMPLEMENT ME
>>>>>>> origin/impl-lukyanov
}

// Проверка на то, что перемещение осуществляется только внутри дерева одного пользователя
// и в ноды с валидными типами
<<<<<<< HEAD
//
void NodeManager::move(size_t node_id, size_t destination_id) {
    Node mv_node = db_->node_dbm()->get(node_id);
    Node mvd_node = mv_node;
    mvd_node.parent_id = destination_id;
    update(mvd_node);

=======
void NodeManager::move(int node_id, int destination_id) {
	const Node& mv_node = db_->node_dbm()->get(node_id); 
	Node mvd_node = mv_node;
	mvd_node.parent_id = destination_id;
>>>>>>> origin/impl-lukyanov
}

// TODO(uma_op): Проверка на права доступа
// Подписка может осуществиться только на PUBLIC_{DIRECTORY | CALENDAR}
<<<<<<< HEAD
void NodeManager::subscribe(size_t node_id) {
    User user = db_->user_dbm()->get();
    Node node = db_->node_dbm()->get(node_id);
=======
void NodeManager::subscribe(int node_id) {
	const User& user = db_->user_dbm()->get();
>>>>>>> origin/impl-lukyanov

    if (!(node.type & (PUBLIC_DIRECTORY | PUBLIC_CALENDAR))) return;

    for (auto subg : db_->node_dbm()->getChildren(user.root_id)) {
        if (subg.type & SUBSCRIPTIONS_GROUP) {
            Node mount_node = {0, subg.id, node_id, MOUNT};
            add(mount_node);
            break;
        }
    }

}

// Отписка является одной из самых безобидных операций
// и не требует никаких проверок
<<<<<<< HEAD
void NodeManager::unsubscribe(size_t node_id) {
    User user = db_->user_dbm()->get();
=======
void NodeManager::unsubscribe(int node_id) {
	const User& user = db_->user_dbm()->get();
>>>>>>> origin/impl-lukyanov

    for (auto subg : db_->node_dbm()->getChildren(user.root_id))
        if (subg.type & SUBSCRIPTIONS_GROUP) {
            for (auto sub : db_->node_dbm()->getChildren(subg.id))
                if (sub.resource_id == node_id) {
                    db_->node_dbm()->remove(sub.id);
                    break;
                }
            break;
        }
}

<<<<<<< HEAD
// Получение детей так же как и получение требует лишь проверки прав доступа
std::vector<Node> NodeManager::getChildren(size_t node_id) {
	User user = db_->user_dbm()->get();
	Node node = db_->node_dbm()->get(node_id);

	if (!(checkAccess(user.id, node_id) || node.type & PUBLIC))
		return std::vector<Node>();

=======
// TODO(uma_op) Получение детей так же как и получение требует лишь проверки прав доступа
std::vector<Node> NodeManager::getChildren(int node_id) {
>>>>>>> origin/impl-lukyanov
	return db_->node_dbm()->getChildren(node_id);
}

bool NodeManager::subscribed(size_t node_id) {
	User user = db_->user_dbm()->get();
	Node root = db_->node_dbm()->get(user.root_id);

	for (auto c : db_->node_dbm()->getChildren(root.id))
		if (c.type & SUBSCRIPTIONS_GROUP)
			for (auto s : db_->node_dbm()->getChildren(c.id))
				if (s.resource_id == node_id)
					return true;

	return false;
}

