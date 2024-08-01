TARGET = 15Puzzle
SUBTARGET = test
LIB_NAME = lib
TEST_NAME = test

TESTFLAGS = -I thirdparty
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
CFLAGS = -I src/lib
DEPSFLAGS = -MMD
CC = clang++

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
TEST_DIR = test

APP_PATH = $(BIN_DIR)/$(TARGET)
TEST_PATH = $(BIN_DIR)/$(TEST_NAME)

APP_SOURCES = $(wildcard $(SRC_DIR)/main/*.cpp)
APP_OBJECTS = $(patsubst $(SRC_DIR)/main/%.cpp, $(OBJ_DIR)/main/%.o, $(APP_SOURCES))

LIB_SOURCES = $(wildcard $(SRC_DIR)/lib/*.cpp)
LIB_OBJECTS = $(patsubst $(SRC_DIR)/lib/%.cpp, $(OBJ_DIR)/lib/%.o, $(LIB_SOURCES))

TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_DIR)/test/%.o, $(TEST_SOURCES))

DEPS = $(APP_OBJECTS:.o=.d) $(LIB_OBJECTS:.o=.d) $(TEST_OBJECTS:.o=.d)

all: $(APP_PATH)

$(APP_PATH): $(APP_OBJECTS) $(LIB_OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(SFML_FLAGS) $(APP_OBJECTS) $(LIB_OBJECTS) -o $@

$(OBJ_DIR)/main/%.o: $(SRC_DIR)/main/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DEPSFLAGS) -c $< -o $@

$(OBJ_DIR)/lib/%.o: $(SRC_DIR)/lib/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DEPSFLAGS) -c $< -o $@

$(OBJ_DIR)/test/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(TESTFLAGS) $(DEPSFLAGS) -c $< -o $@

test: $(TEST_PATH)

$(TEST_PATH): $(TEST_OBJECTS) $(LIB_OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(SFML_FLAGS) $(TEST_OBJECTS) $(LIB_OBJECTS) -o $@
	./$(TEST_PATH)

clear:
	$(RM) $(APP_PATH) $(TEST_PATH) $(OBJ_DIR)/*/*.o $(OBJ_DIR)/*/*.d

-include $(DEPS)
