#include "User_db_model.hpp"

namespace dbo = Wt::Dbo;

using UserDatabase = Wt::Auth::Dbo::UserDatabase<AuthInfo>;

class Session : public dbo::Session
{
public:
  Session(const std::string& sqliteDb);

  Wt::Auth::AbstractUserDatabase& userss();
  Wt::Auth::Login& login() { return login_; }


private:
  std::unique_ptr<UserDatabase> users_;
  Wt::Auth::Login login_;


};