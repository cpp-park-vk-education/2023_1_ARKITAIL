#include <iterator>
#include <memory>
#include <mutex>
#include <thread>
#include <utility>

#include "CalendarDbManagerMock.hpp"
#include "CommentDbManagerMock.hpp"
#include "DbMock.hpp"
#include "DirectoryDbManagerMock.hpp"
#include "EventDbManagerMock.hpp"
#include "EventManager.hpp"
#include "NodeDbManagerMock.hpp"
#include "ProfileDbManagerMock.hpp"
#include "ProfileManager.hpp"
#include "TagDbManagerMock.hpp"
#include "UserDbManagerMock.hpp"
#include "CalendarManager.hpp"
#include "DbManagers.hpp"
#include "DirectoryManager.hpp"
#include "IDbManagers.hpp"
#include "NodeManager.hpp"
#include "UserManager.hpp"
#include "Managers.hpp"
#include "SessionScopeMap.hpp"
#include "SessionScope.hpp"
#include "EventManager.hpp"

SessionScopeMap::SessionScopeMap() {}

SessionScopeMap& SessionScopeMap::instance() {
	static SessionScopeMap ssm;
	return ssm;
}

SessionScope* SessionScopeMap::get() {
	std::lock_guard<std::mutex> lg(container_mutex_);

	auto tid = std::this_thread::get_id();
	auto ss = container_.find(tid);

	if (ss == container_.end()) {
		add(tid);
		ss = container_.find(tid);  // Можно было бы возвращать итератор из add
	}

	return ss->second.get();
}

void SessionScopeMap::add(std::thread::id tid) {
	std::shared_ptr<DbMock> db_mock = std::make_shared<DbMock>();

	std::shared_ptr<IDbManagers> db = std::make_shared<DbManagers>(
		std::make_unique<UserDbManagerMock>(db_mock),
		std::make_unique<NodeDbManagerMock>(db_mock),
		std::make_unique<DirectoryDbManagerMock>(db_mock),
		std::make_unique<CalendarDbManagerMock>(db_mock),
		std::make_unique<EventDbManagerMock>(db_mock),
		std::make_unique<CommentDbManagerMock>(),
		std::make_unique<TagDbManagerMock>(),
		std::make_unique<ProfileDbManagerMock>()
	);

	container_.insert(
		std::make_pair(
			tid,
			std::make_unique<SessionScope>(
				std::make_unique<Managers>(
					std::make_unique<UserManager>(db),
					std::make_unique<NodeManager>(db),
					std::make_unique<DirectoryManager>(db),
					std::make_unique<CalendarManager>(db),
					std::make_unique<EventManager>(db),
					std::make_unique<ProfileManager>(db)
				),
				std::make_unique<ConnectionsMediator>()
			)
		)
	);
}

void SessionScopeMap::remove() {
	std::lock_guard<std::mutex> lg(container_mutex_);

	auto tid = std::this_thread::get_id();

	container_.erase(tid);
}

