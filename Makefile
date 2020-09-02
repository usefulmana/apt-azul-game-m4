CC := g++
CFLAGS := -Wall -Werror -std=c++14 -g -O
TARGET := bin/azul

# $(wildcard *.cpp /xxx/xxx/*.cpp): get all .cpp files from the current directory and dir "/xxx/xxx/"
SRCS := $(wildcard src/*.cpp)
# $(patsubst %.cpp,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
OBJS := $(patsubst %.cpp, %.o, $(SRCS))

all: $(TARGET)

src/%.o: %.cpp
	$(CC) $(CFLAGS) -c $^

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^



clean:
	rm -f $(TARGET) src/*.o

.PHONY: all clean
