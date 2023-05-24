#pragma once

#include <istream>
#include <memory>

#include <Wt/WStreamResource.h>
#include <Wt/Http/Request.h>
#include <Wt/Http/Response.h>

class StringStreamResource : public Wt::WStreamResource{
 public:
  StringStreamResource(std::unique_ptr<std::istream>&& source);
  ~StringStreamResource();

  void handleRequest(
      const Wt::Http::Request& request,
      Wt::Http::Response& response) override;
 private:
  std::unique_ptr<std::istream> source_;
};
