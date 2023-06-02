#pragma once

#include "CalendarManagerStub.hpp"
#include "IManagers.hpp"

class ManagersStub : public IManagers {
  public:
    ManagersStub();

    IUserManager* user_manager() override;
    INodeManager* node_manager() override;
    IDirectoryManager* directory_manager() override;
    ICalendarManager* calendar_manager() override;
    IEventManager* event_manager() override;
    IProfileManager* profile_manager() override;
    ITagManager* tag_manager() override;

  private:
    std::unique_ptr<IUserManager> user_manager_;
    std::unique_ptr<INodeManager> node_manager_;
    std::unique_ptr<IDirectoryManager> directory_manager_;
    std::unique_ptr<ICalendarManager> calendar_manager_;
    std::unique_ptr<IEventManager> event_manager_;
    std::unique_ptr<IProfileManager> profile_manager_;
    std::unique_ptr<ITagManager> tag_manager_;
};
