APP_NAME = main
LIB_NAME = lib

CFLAGS = -lsfml-graphics -lsfml-system -lsfml-window -I src
DEPSFLAGS = 
CC = g++

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src

APP_PATH = $(BIN_DIR)/$(APP_NAME)
LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/$(LIB_NAME).a

APP_SOURCES = $(wildcard $(SRC_DIR)/$(APP_NAME)/*.cpp)
APP_OBJECTS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(APP_SOURCES))

LIB_SOURCES = $(wildcard $(SRC_DIR)/$(LIB_NAME)/*.cpp)
LIB_OBJECTS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(LIB_SOURCES))

DEPS = $(APP_OBJECTS:.o=.d) $(LIB_OBJECTS:.o=.d)

all: $(APP_PATH)

-include $(DEPS)


$(APP_PATH): $(APP_OBJECTS) $(LIB_PATH)
	$(CC) $(CFLAGS) -o $@ $^

$(LIB_PATH): $(LIB_OBJECTS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(DEPSFLAGS) -c -o $@ $< 

clear:
	$(RM) $(APP_PATH) $(OBJ_DIR)/*/*/*.[aod]
