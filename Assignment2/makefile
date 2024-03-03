CC = g++
CFLAGS = -std=c++17 -Wall -Wextra
SFMLFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image 

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

EXECUTABLE = $(BIN_DIR)/program.exe

all:
	g++ -std=c++17 -Wall -Wextra -Iinclude -Llib src/main.cpp -o main.exe -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
# all: $(EXECUTABLE)

# $(EXECUTABLE): $(OBJ_FILES)
# 	@mkdir -p $(BIN_DIR)
# 	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -Llib $^ -o $@ $(SFMLFLAGS)

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
# 	@mkdir -p $(OBJ_DIR)
# 	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -Llib -c $< -o $@

# clean:
# 	rm -rf $(OBJ_DIR) $(BIN_DIR)

# .PHONY: all clean

