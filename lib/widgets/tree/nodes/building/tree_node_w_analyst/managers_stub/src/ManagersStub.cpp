#include "ManagersStub.hpp"

#include <vector>

#include "Calendar.hpp"
#include "CalendarManagerStub.hpp"
#include "Directory.hpp"
#include "DirectoryManagerStub.hpp"
#include "NodeManagerStub.hpp"
#include "ProfileManagerStub.hpp"
#include "UserManagerStub.hpp"

ManagersStub::ManagersStub() {
    auto users = std::vector<User>{
        User(0, 0, "login", "email", "nickname", "desc")};
    user_manager_ = std::make_unique<UserManagerStub>(users);

    auto directories = std::vector<Directory>{
        Directory(0, 0, 0, "testRoot", "root desc"),
        Directory(100, 100, 1, "testRoot", "root desc"),
        Directory(1, 1, 0, "testPrivateGroup", "testPrivateGroup desc"),
        Directory(2, 2, 0, "testPublicGroup", "testPublicGroup desc"),
        Directory(3, 3, 0, "testSubscriptionsGroup", "testSubscriptionsGroup desc"),
        Directory(4, 4, 0, "testProfileGroup", "testProfileGroup desc"),

        Directory(5, 5, 0, "testPrivateDir", "testPrivateDir desc"),
        Directory(6, 6, 0, "testPrivateDir", "testPrivateDir desc"),

        Directory(7, 7, 0, "testPublicDir", "testPublicDir desc"),
        Directory(8, 8, 0, "testPublicDir", "testPublicDir desc"),

        Directory(9, 9, 0, "testSubMountDir", "testSubMountDir desc"),
        Directory(10, 10, 0, "testSubDir", "testSubDir desc"),
        Directory(11, 11, 0, "testSubDir", "testSubDir desc"),

        Directory(12, 19, 0, "testOtherRootDir", "testOtherRootDir desc"),
        Directory(13, 20, 0, "testOtherDir", "testSubDir desc"),
        Directory(14, 21, 0, "testOtherDir", "testSubDir desc"),
    };
    directory_manager_ = std::make_unique<DirectoryManagerStub>(directories);

    auto calendars = std::vector<Calendar>{
        Calendar(0, 12, 0, "PrivateCalendar", "PrivateCalendar desc",
                     CalendarVisibility::kPrivate, Wt::WColor()),
        Calendar(1, 13, 0, "PrivateCalendar", "PrivateCalendar desc",
                     CalendarVisibility::kPrivate, Wt::WColor()),
        
        Calendar(3, 14, 0, "PublicCalendar", "PublicCalendar desc",
                     CalendarVisibility::kPublic, Wt::WColor()),
        Calendar(4, 15, 0, "PublicCalendar", "PublicCalendar desc",
                     CalendarVisibility::kPublic, Wt::WColor()),

        Calendar(5, 16, 0, "testSubMountCalendar", "testSubMountCalendar desc",
                     CalendarVisibility::kPublic, Wt::WColor()),
        Calendar(6, 17, 0, "testSubCalendar", "testSubCalendar desc",
                     CalendarVisibility::kPublic, Wt::WColor()),
        Calendar(7, 18, 0, "testSubCalendar", "testSubCalendar desc",
                     CalendarVisibility::kPublic, Wt::WColor()),
        
        Calendar(8, 22, 0, "testOtherRootCalendar", "testOtherRootCalendar desc",
                     CalendarVisibility::kPublic, Wt::WColor()),
        Calendar(9, 23, 0, "testOtherCalendar", "testOtherCalendar desc",
                     CalendarVisibility::kPublic, Wt::WColor()),
    };

    calendar_manager_ = std::make_unique<CalendarManagerStub>(calendars);

    auto profiles = std::vector<Profile>{
        Profile(0, 24, 0, std::vector<int>{12, 21}, "Profile"),
        Profile(1, 25, 0, std::vector<int>{12, 21}, "Profile"),
    };

    profile_manager_ = std::make_unique<ProfileManagerStub>(profiles);
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
