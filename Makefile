CC=g++
CFLAGS=-I include
EXEC=Application
SOURCES := $(wildcard src/*.cpp)
OBJECTS := $(SOURCES:src/%.cpp=obj/%.o)
UNAME := $(shell uname -s)

ifeq ($(UNAME),Darwin)
FLAGS_ALL = -framework SDL2 -framework OPENGL
endif

ifeq ($(UNAME), Linux)
CFLAGS += -D__LINUX__ -DGL_GLEXT_PROTOTYPES -DGL3_PROTOTYPES=1
FLAGS_ALL = -lGL -lGLEW `sdl2-config --cflags --libs`
endif

all: $(OBJECTS)
	@echo "Flags: "$(FLAGS_ALL)
	@echo "Unix Name: "$(UNAME)
	$(CC) -g -O0 -o $(EXEC) $^ $(FLAGS_ALL)

$(OBJECTS): obj/%.o : src/%.cpp
	$(CC) -c $< -o $@ $(CFLAGS)
	@echo "Compiled "$<" successfully!"

clean:
	rm -rf obj/*.o
	rm -rf Application

run: all
	./Application
