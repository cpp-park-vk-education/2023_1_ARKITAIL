#pragma once

#include <memory>
#include <istream>

#include <Wt/WStreamResource.h>
#include <Wt/Http/Request.h>
#include <Wt/Http/Response.h>

#include "IStreamBuffer.hpp"

class StringStreamResource : public Wt::WStreamResource{
 public:
  StringStreamResource(std::unique_ptr<parsing::IStreamBuffer>&& buffer);
  ~StringStreamResource();

  void handleRequest(
      const Wt::Http::Request& request,
      Wt::Http::Response& response) override;
 private:
  std::istream is_;
};
