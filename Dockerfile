FROM alpine:3.17.3

RUN apk update && \
    apk add --no-cache \
      build-base \
      cmake \
      boost-dev \
      libpq-dev \
      wt-dev \
      gtest-dev

WORKDIR /calendula/
