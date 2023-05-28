#include "StringStreamResource.hpp"

#include <memory>

#include <Wt/WStreamResource.h>

StringStreamResource::StringStreamResource(
    std::unique_ptr<std::istream>&& source)
    : Wt::WStreamResource("text/calendar"),
      source_(std::move(source)) {
  suggestFileName("calendar.ics");
}

StringStreamResource::~StringStreamResource() {
  beingDeleted();
}

void StringStreamResource::handleRequest(
    const Wt::Http::Request &request,
    Wt::Http::Response &response) {
  handleRequestPiecewise(request, response, *source_);
}
