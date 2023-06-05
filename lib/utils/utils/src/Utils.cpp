#include "Utils.hpp"

#include <array>
#include <iostream>
#include <sstream>
#include <string>

std::string GetConnectionInformation() {
  const std::size_t kParametersCount = 5;
  
  // специально указываю хранимый тип не 'std::string', потому что дальше 
  // передаю элементы в функцию std::getenv, которая принимает 'const char*'
  const std::array<const char*, kParametersCount> kEnvironmentVariables {
    "DB_HOST",
    "DB_PORT",
    "DB_NAME",
    "DB_USER",
    "DB_PASSWORD",
  };

  const std::array<std::string, kParametersCount> kKeywords {
    "host",
    "port",
    "dbname",
    "user",
    "password",
  };

  std::stringstream connection_information;
  for (std::size_t i = 0; i < kParametersCount; i++) {
    auto value = std::getenv(kEnvironmentVariables[i]);
    if (value) {
      connection_information << kKeywords[i] << '=' << value << '\n';
    } else {
      std::cerr 
        << kEnvironmentVariables[i] << " environment variable is not found" 
        << std::endl;
    }
  }
  return connection_information.str();
}
