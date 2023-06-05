#include <memory>

#include "IProfileManager.hpp"
#include "Node.hpp"
#include "Profile.hpp"
#include "ProfileManager.hpp"
#include "IDbManagers.hpp"
#include "SessionScopeMap.hpp"

ProfileManager::ProfileManager(std::shared_ptr<IDbManagers> db) :
	db_(db) {}

ProfileSptr ProfileManager::get(int profile_id) {
    ProfileSptr profile = db_->profile_dbm()->get(profile_id);
    std::cout << "PROFILE ID " << profile_id << " " << profile->id << std::endl;
	return profile;
}

int ProfileManager::add(ProfileSptr profile, int directory_id) {
	auto mgr = SessionScopeMap::instance().get()->managers();

    UserSptr user = db_->user_dbm()->get();
    profile->owner_id = user->id;

    DirectorySptr parent_directory = mgr->directory_manager()->get(directory_id);

    std::cout << "ProfileManager::add1" << std::endl;
    if (!parent_directory->id || user->id != parent_directory->owner_id)
        return 0;

    NodeSptr parent_node = mgr->node_manager()->get(mgr->directory_manager()->get(directory_id)->node_id);
    NodeSptr new_node = std::make_shared<Node>(
        0, parent_node->id, 0, parent_node->owner_id, PROFILE);

    new_node->id = mgr->node_manager()->add(new_node);

    if (!new_node->id)
        return 0;

    profile->node_id = new_node->id;

    profile->id = db_->profile_dbm()->add(profile);
    new_node->resource_id = profile->id;
    db_->node_dbm()->update(new_node);
    mgr->node_manager()->update(new_node);

    return profile->id;
}

void ProfileManager::update(ProfileSptr profile) {
	db_->profile_dbm()->update(profile);
}

void ProfileManager::remove(int profile_id) {
	db_->profile_dbm()->remove(profile_id);
}

