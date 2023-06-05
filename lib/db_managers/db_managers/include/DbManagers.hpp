#pragma once

#include <memory>

#include "IDbManagers.hpp"
#include "IUserDbManager.hpp"
#include "INodeDbManager.hpp"
#include "IDirectoryDbManager.hpp"
#include "ICalendarDbManager.hpp"
#include "IEventDbManager.hpp"
#include "ICommentDbManager.hpp"
#include "ITagDbManager.hpp"
#include "IProfileDbManager.hpp"

class DbManagers : public IDbManagers {
public:
  DbManagers() = default;
	DbManagers(
		std::unique_ptr<IUserDbManager> user_dbm,
		std::unique_ptr<INodeDbManager> node_dbm,
		std::unique_ptr<IDirectoryDbManager> directory_dbm,
		std::unique_ptr<ICalendarDbManager> calendar_dbm,
		std::unique_ptr<IEventDbManager> event_dbm,
		std::unique_ptr<ICommentDbManager> comment_dbm,
		std::unique_ptr<ITagDbManager> tag_dbm,
		std::unique_ptr<IProfileDbManager> profile_dbm
	);

	IUserDbManager* user_dbm() override;
	INodeDbManager* node_dbm() override;
	IDirectoryDbManager* directory_dbm() override;
	ICalendarDbManager* calendar_dbm() override;
	IEventDbManager* event_dbm() override;
	ICommentDbManager* comment_dbm() override;
	ITagDbManager* tag_dbm() override;
	IProfileDbManager* profile_dbm() override;

private:
	std::unique_ptr<IUserDbManager> user_dbm_;
	std::unique_ptr<INodeDbManager> node_dbm_;
	std::unique_ptr<IDirectoryDbManager> directory_dbm_;
	std::unique_ptr<ICalendarDbManager> calendar_dbm_;
	std::unique_ptr<IEventDbManager> event_dbm_;
	std::unique_ptr<ICommentDbManager> comment_dbm_;
	std::unique_ptr<ITagDbManager> tag_dbm_;
	std::unique_ptr<IProfileDbManager> profile_dbm_;

};
 
