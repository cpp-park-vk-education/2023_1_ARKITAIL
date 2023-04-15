FROM alpine:3.17.3

RUN apk update && \
    apk add --no-cache \
      build-base \
      cmake \
      libstdc++ \
      boost-dev \
      wt-dev \
      gtest-dev

WORKDIR /calendula/
