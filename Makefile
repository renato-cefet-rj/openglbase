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
# comment this line if your machine is not OpenGL 3.3. capable (e.g. 3.0 only)
#OPENGL_CAP = -DOpenGL33_OK

CFLAGS += -DLinux $(OPENGL_CAP)
FLAGS_ALL = -lGL -lGLEW `sdl2-config --cflags --libs`
endif

all: $(OBJECTS)
	@echo "Flags: "$(FLAGS_ALL)
	@echo "Unix Name: "$(UNAME)
	$(CC) -o $(EXEC) $^ $(FLAGS_ALL)

$(OBJECTS): obj/%.o : src/%.cpp
	$(CC) -c $< -o $@ $(CFLAGS)
	@echo "Compiled "$<" successfully!"

clean:
	rm -rf obj/*.o
	rm -rf Application

run: all
	./Application
