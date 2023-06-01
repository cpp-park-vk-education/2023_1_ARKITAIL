#pragma once

#include <vector>

#include "DbMock.hpp"
#include "IProfileDbManager.hpp"
#include "Profile.hpp"

class ProfileDbManagerMock : public IProfileDbManager {
public:
	ProfileDbManagerMock(std::shared_ptr<DbMock> db);

	ProfileSptr get(size_t profile_id) override;
	size_t add(ProfileSptr profile) override;
	void update(ProfileSptr profile) override;
	void remove(size_t profile_id) override;

private:
	std::shared_ptr<DbMock> db_;
	size_t aid_;

};

