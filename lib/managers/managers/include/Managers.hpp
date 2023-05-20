#pragma once

#include <memory>

#include "IManagers.hpp"
#include "IUserManager.hpp"
#include "IDirectoryManager.hpp"
#include "ICalendarManager.hpp"
#include "INodeManager.hpp"

class Managers : public IManagers {
public:
	Managers(
		std::unique_ptr<IUserManager> user_manager,
		std::unique_ptr<INodeManager> node_manager,
		std::unique_ptr<IDirectoryManager> directory_manager,
		std::unique_ptr<ICalendarManager> calendar_manager
	);

	IUserManager* user_manager() override;
	INodeManager* node_manager() override;
	IDirectoryManager* directory_manager() override;
	ICalendarManager* calendar_manager() override;

private:
	std::unique_ptr<IUserManager> user_manager_;
	std::unique_ptr<INodeManager> node_manager_;
	std::unique_ptr<IDirectoryManager> directory_manager_;
	std::unique_ptr<ICalendarManager> calendar_manager_;

};

