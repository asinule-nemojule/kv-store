FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    g++ \
    make \
    && rm -rf /var/lib/apt/lists/*

COPY src /app/src
COPY Makefile /app/

WORKDIR /app
RUN make clean && make

EXPOSE 8080
CMD ["./kv_server"]
