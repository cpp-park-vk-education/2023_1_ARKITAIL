#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>
#include <Wt/Dbo/Types.h>
#include <Wt/WGlobal.h>
#include <string>
#include <chrono>
#include <array>
#include <Wt/Auth/Login.h>
#include <Wt/Auth/Dbo/UserDatabase.h>
#include <Wt/Auth/Dbo/AuthInfo.h>
#include <Wt/Dbo/Session.h>
#include <Wt/Dbo/ptr.h>
#include <fstream>
#include <vector>

namespace dbo = Wt::Dbo;