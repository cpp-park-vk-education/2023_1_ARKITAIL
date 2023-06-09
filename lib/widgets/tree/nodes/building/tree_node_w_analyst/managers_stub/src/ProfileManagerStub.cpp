#include "ProfileManagerStub.hpp"

ProfileManagerStub::ProfileManagerStub(std::vector<Profile> profiles) :
    profiles_(profiles) {}

ProfileSptr ProfileManagerStub::get(int profile_id) {
    for (auto e = profiles_.begin(); e != profiles_.end(); e++)
        if (e->id == profile_id)
            return std::make_shared<Profile>(*e);

    return std::make_shared<Profile>(profiles_[0]);
}
