#include "session.hpp"
#include "User_db_model.hpp"

#include "base_for_all.hpp"

using namespace Wt;

Session::Session(const std::string &postgreDB) {
  auto pg = std::make_unique<Dbo::backend::Postgres>(postgreDB);
  setConnection(std::move(pg));
  
  mapClass<users>("users_");
  mapClass<AuthInfo>("auth_info");
  mapClass<AuthInfo::AuthIdentityType>("auth_identity");
  mapClass<AuthInfo::AuthTokenType>("auth_token");

  try {
    createTables();
    std::cerr << "Created database." << std::endl;
  } catch (Wt::Dbo::Exception &e) {
    std::cerr << e.what() << std::endl;
    std::cerr << "Using existing database";
  }

  users_ = std::make_unique<UserDatabase>(*this);
}
