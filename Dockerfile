FROM alpine:3.17.3

RUN apk update && \
    apk add --no-cache \
      build-base \
      cmake \
      boost-dev \
      wt-dev \
      postgresql-dev \
      gtest-dev

WORKDIR /calendula

COPY . .

RUN make generate build

CMD [ "./build/Calendula" ]
