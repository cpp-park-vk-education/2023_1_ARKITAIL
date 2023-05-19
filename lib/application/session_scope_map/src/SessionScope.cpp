#include <memory>

#include "UserManager.hpp"
#include "NodeManager.hpp"
#include "DirectoryManager.hpp"
#include "CalendarManager.hpp"

#include "UserDbManagerMock.hpp"
#include "NodeDbManagerMock.hpp"
#include "DirectoryDbManagerMock.hpp"
#include "CalendarDbManagerMock.hpp"
#include "EventDbManagerMock.hpp"
#include "CommentDbManagerMock.hpp"
#include "TagDbManagerMock.hpp"
#include "ProfileDbManagerMock.hpp"

#include "SessionScope.hpp"
#include "ConnectionsMediator.hpp"

SessionScope::SessionScope() :
	managers(
		std::make_unique<UserManager>(),
		std::make_unique<NodeManager>(),
		std::make_unique<DirectoryManager>(),
		std::make_unique<CalendarManager>()
	),
	db_managers(
		std::make_unique<UserDbManagerMock>(),
		std::make_unique<NodeDbManagerMock>(),
		std::make_unique<DirectoryDbManagerMock>(),
		std::make_unique<CalendarDbManagerMock>(),
		std::make_unique<EventDbManagerMock>(),
		std::make_unique<CommentDbManagerMock>(),
		std::make_unique<TagDbManagerMock>(),
		std::make_unique<ProfileDbManagerMock>()
	),
	connections_mediator() {}

