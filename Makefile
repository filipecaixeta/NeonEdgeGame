CC=g++
RMDIR = rm -rf
RM = rm -f
DEP_FLAGS = -MT $@ -MMD -MP -MF $(DEP_PATH)/$*.d -I/usr/include/SDL2
DIRECTIVES = -std=c++11 -Wall -Wextra -c -I $(HEADER_PATH) -Bstatic -static-libgcc
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm

HEADER_PATH = include
SRC_PATH = src
BIN_PATH = build
DEP_PATH = build

CPP_FILES = $(wildcard $(SRC_PATH)/*.cpp)
CPP_FILES += $(wildcard $(SRC_PATH)/menu/*.cpp)
OBJ_FILES = $(addprefix $(BIN_PATH)/,$(notdir $(CPP_FILES:.cpp=.o)))
DEP_FILES = $(wildcard $(DEP_PATH)/*.d)

EXEC = bin/Game

ifeq ($(OS),Windows_NT)

RMDIR = rd /s /q
RM = del

SDL_PATH = C:\SDL2.x.x

DIRECTIVES += -I $(SDL_PATH)\include\SDL2

LIBS = -L $(SDL_PATH)\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm

EXEC := $(EXEC).exe

else
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
LIBS = -lm -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_ttf

endif
endif

all: $(EXEC)

$(EXEC): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LIBS)

$(BIN_PATH)/%.o: $(SRC_PATH)/%.cpp
ifeq ($(OS),Windows_NT)
	@if not exist $(DEP_PATH) @mkdir $(DEP_PATH)
	@if not exist $(BIN_PATH) @mkdir $(BIN_PATH)
else
	@mkdir -p $(DEP_PATH) $(BIN_PATH)
endif

	$(CC) $(DEP_FLAGS) -c -o $@ $< $(DIRECTIVES)


$(BIN_PATH)/%.o: $(SRC_PATH)/menu/%.cpp
ifeq ($(OS),Windows_NT)
	@if not exist $(DEP_PATH) @mkdir $(DEP_PATH)
	@if not exist $(BIN_PATH) @mkdir $(BIN_PATH)
else
	@mkdir -p $(DEP_PATH) $(BIN_PATH)
endif

	$(CC) $(DEP_FLAGS) -c -o $@ $< $(DIRECTIVES)


clean:
	$(RMDIR) $(BIN_PATH) $(DEP_PATH)
	$(RM) $(EXEC)

-include $(DEP_FILES)

.PRECIOUS: $(DEP_PATH)/%.d

.PHONY: debug clean release

print-% : ; @echo $* = $($*)

debug: DIRECTIVES += -ggdb -O0
debug: all

release: DIRECTIVES += -Ofast -mtune=native
release: all