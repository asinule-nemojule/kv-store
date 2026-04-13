CXX = g++
CXXFLAGS = -std=c++17 -pthread -Wall -O2
TARGET = kv_server

SRCS = src/server.cpp src/store.cpp src/thread_pool.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
