#include <memory>

#include "IProfileManager.hpp"
#include "Node.hpp"
#include "Profile.hpp"
#include "ProfileManager.hpp"
#include "IDbManagers.hpp"
#include "SessionScopeMap.hpp"

ProfileManager::ProfileManager(std::shared_ptr<IDbManagers> db) :
	db_(db) {}

ProfileSptr ProfileManager::get(size_t profile_id) {
    ProfileSptr profile = db_->profile_dbm()->get(profile_id);
    std::cout << "PROFILE ID " << profile_id << " " << profile->id << std::endl;
	return profile;
}

size_t ProfileManager::add(ProfileSptr profile, size_t directory_id) {
	auto mgr = SessionScopeMap::instance().get()->managers();

    User user = db_->user_dbm()->get();
    profile->owner_id = user.id;

    Directory parent_directory = mgr->directory_manager()->get(directory_id);

    std::cout << "ProfileManager::add1" << std::endl;
    if (!parent_directory.id || user.id != parent_directory.owner_id)
        return 0;

    Node parent_node = mgr->node_manager()->get(mgr->directory_manager()->get(directory_id).node_id);
    Node new_node = {0, parent_node.id, 0, PROFILE};

    new_node.id = mgr->node_manager()->add(new_node);

    if (!new_node.id)
        return 0;

    profile->node_id = new_node.id;

    profile->id = db_->profile_dbm()->add(profile);
    new_node.resource_id = profile->id;
    db_->node_dbm()->update(new_node);
    mgr->node_manager()->update(new_node);

    return profile->id;
}

void ProfileManager::update(ProfileSptr profile) {
	db_->profile_dbm()->update(profile);
}

void ProfileManager::remove(size_t profile_id) {
	db_->profile_dbm()->remove(profile_id);
}

