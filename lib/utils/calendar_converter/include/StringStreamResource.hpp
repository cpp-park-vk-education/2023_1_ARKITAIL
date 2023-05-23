#pragma once

#include <memory>
#include <sstream>

#include <Wt/WStreamResource.h>
#include <Wt/Http/Request.h>
#include <Wt/Http/Response.h>

#include "IStreamBuffer.hpp"

class StringStreamResource : public Wt::WStreamResource{
 public:
  StringStreamResource(std::stringstream&& ss);
  ~StringStreamResource();

  void handleRequest(
      const Wt::Http::Request& request,
      Wt::Http::Response& response) override;
 private:
  std::stringstream ss_;
};
