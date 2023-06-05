#pragma once

#include <vector>

#include "DbMock.hpp"
#include "IProfileDbManager.hpp"
#include "Profile.hpp"

class ProfileDbManagerMock : public IProfileDbManager {
public:
	ProfileDbManagerMock(std::shared_ptr<DbMock> db);

	ProfileSptr get(int profile_id) override;
	int add(ProfileSptr profile) override;
	void update(ProfileSptr profile) override;
	void remove(int profile_id) override;

private:
	std::shared_ptr<DbMock> db_;
	int aid_;

};

