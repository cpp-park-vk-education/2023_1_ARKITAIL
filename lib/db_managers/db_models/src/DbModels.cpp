#include "DbModels.hpp"

#include <fstream>
#include <string>
#include <vector>

#include <Wt/Dbo/Impl.h>

namespace db {
std::vector<unsigned char> ReadFile(const std::string &filename) {
  std::ifstream file(filename, std::ios::binary);
  return std::vector<unsigned char>(std::istreambuf_iterator<char>(file),
                                    std::istreambuf_iterator<char>());
}
} // namespace db

DBO_INSTANTIATE_TEMPLATES(db::User);
