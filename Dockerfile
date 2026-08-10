FROM ubuntu:24.04 AS build
RUN apt-get update && apt-get install -y g++ cmake && rm -rf /var/lib/apt/lists/*
WORKDIR /app
COPY . .
RUN cmake -S . -B build && cmake --build build -j2
CMD ["./build/pulsegrid"]
