#include <memory>

#include "SessionScope.hpp"
#include "CalendarDbManagerMock.hpp"
#include "ConnectionsMediator.hpp"
#include "DirectoryDbManagerMock.hpp"
#include "Managers.hpp"
#include "NodeDbManagerMock.hpp"
#include "UserDbManagerMock.hpp"
#include "EventDbManagerMock.hpp"
#include "CommentDbManagerMock.hpp"
#include "TagDbManagerMock.hpp"
#include "ProfileDbManagerMock.hpp"

SessionScope::SessionScope() :
	managers(),
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

