# Key-Value Store in C++

A multi-threaded, in-memory key-value store server built in C++17. Supports concurrent clients with thread-safe operations.

## Features

- **SET key value** - Store a key-value pair
- **GET key** - Retrieve value by key
- **DELETE key** - Remove key-value pair
- **COUNT** - Get total number of keys in store

## Technologies

- C++17
- POSIX sockets
- Thread pool with `std::shared_mutex`
- Linux / WSL2
- Docker containerization

## How to Build and Run

### Native (Linux/WSL)

`make`
`./kv_server`

## DOCKER

`docker build -t kv-store .`
`docker run -p 8080:8080 kv-store`

## Testing

Open another terminal and use telnet or netcat: 

`telnet localhost 8080`

Commands:
`SET name Vukasin
OK
GET name
Vukasin
COUNT
1
DELETE name
DELETED`

## Benchmarking results

Metric                           Value
Requests per second             ~10,000+
Concurrency                    4 worker threads
Protocol                         Raw TCP


## Project Structure

kv-store/ 
├── src/ 
│   ├── server.cpp 
│   ├── store.cpp 
│   ├── store.h 
│   ├── thread_pool.cpp 
│   └── thread_pool.h 
├── Makefile 
├── Dockerfile 
├── .dockerignore 
└── README.md 

Author
Vukasin Nikolic


