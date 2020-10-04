CXX := g++
CXX_FLAGS := -Wall -Werror -g -std=c++14 -O
TARGET := bin/azul
OBJ_DIR := obj

OBJ = $(addprefix $(OBJ_DIR)/, $(patsubst %.cpp, %.o, $(wildcard *.cpp)))

.PHONY: all clean

all: $(OBJ_DIR) $(TARGET)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^

clean:
	@rm -f $(TARGET) $(wildcard *.o)
	@rm -rf $(OBJ_DIR)
