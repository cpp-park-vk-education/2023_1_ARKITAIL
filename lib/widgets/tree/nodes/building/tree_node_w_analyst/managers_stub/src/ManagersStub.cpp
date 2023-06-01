#include "ManagersStub.hpp"

#include <vector>

#include "Calendar.hpp"
#include "CalendarManagerStub.hpp"
#include "Directory.hpp"
#include "DirectoryManagerStub.hpp"
#include "UserManagerStub.hpp"

ManagersStub::ManagersStub() {
    auto users = std::vector<User>{User(0, 0, "login", "email", "nickname", "desc")};
    user_manager_ = std::make_unique<UserManagerStub>(users);

    auto directories = std::vector<Directory>{
        Directory(0, 0, 0, "testRoot", "desc"),
        Directory(1, 1, 0, "testPrivate", "desc"),
        Directory(2, 2, 0, "testPublic", "desc"),
        Directory(3, 3, 0, "testSubscriptions", "desc"),
    };
    directory_manager_ = std::make_unique<DirectoryManagerStub>(directories);

    auto calendars = std::vector<Calendar>{};

    calendar_manager_ = std::make_unique<CalendarManagerStub>(calendars);
}

IUserManager* ManagersStub::user_manager() {
    return user_manager_.get();
}

INodeManager* ManagersStub::node_manager() {
    return node_manager_.get();
}

IDirectoryManager* ManagersStub::directory_manager() {
    return directory_manager_.get();
}

ICalendarManager* ManagersStub::calendar_manager() {
    return calendar_manager_.get();
}

IEventManager* ManagersStub::event_manager() {
    return event_manager_.get();
}

IProfileManager* ManagersStub::profile_manager() {
    return profile_manager_.get();
}

ITagManager* ManagersStub::tag_manager() {
    return tag_manager_.get();
}
