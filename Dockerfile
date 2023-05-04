FROM alpine:3.17.3

RUN apk update && \
    apk add --no-cache \
      build-base \
      cmake \
      wt-dev \
      gtest-dev

WORKDIR /calendula/