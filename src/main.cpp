#include <exception>
#include <memory>

#include <Wt/WApplication.h>
#include <Wt/WConfig.h>
#include <Wt/WGlobal.h>
#include <Wt/WServer.h>

#include "Application.hpp"
#include "Session.hpp"

std::unique_ptr<Wt::WApplication> CreateApplication(const Wt::WEnvironment& env) {
  return std::make_unique<Application>(env);
}

int main(int argc, char* argv[]) {
  try {
    Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);

    server.addEntryPoint(Wt::EntryPointType::Application, CreateApplication);

    Session::ConfigureAuth();

    server.run();
  } catch (Wt::WServer::Exception& e) {
    std::cerr << "Wt::WServer exception: " << e.what() << std::endl;
  } catch (Wt::Dbo::Exception& e) {
    std::cerr << "Wt::Dbo exception: " << e.what() << std::endl;
  } catch (std::exception& e) {
    std::cerr << "exception: " << e.what() << std::endl;
  }
  return 0;
}
