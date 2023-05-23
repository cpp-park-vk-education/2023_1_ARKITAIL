#include "StringStreamResource.hpp"

#include <sstream>

#include <Wt/WStreamResource.h>

#include "IStreamBuffer.hpp"

StringStreamResource::StringStreamResource(std::stringstream&& ss)
    : Wt::WStreamResource("text/calendar"),
      ss_(std::move(ss)) {
  suggestFileName("calendar.ics");
}

StringStreamResource::~StringStreamResource() {
  beingDeleted();
}

void StringStreamResource::handleRequest(
    const Wt::Http::Request &request,
    Wt::Http::Response &response) {
  handleRequestPiecewise(request, response, ss_);
}
