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
endif

all: $(OBJECTS)
	@echo "Flags: "$(FLAGS_ALL)
	@echo "Unix Name: "$(UNAME)".."
	$(CC) -o $(EXEC) $^ $(FLAGS_ALL)

$(OBJECTS): obj/%.o : src/%.cpp
	$(CC) -c $< -o $@ $(CFLAGS)
	@echo "Compiled "$<" successfully!"

clean:
	rm -rf obj/*
	rm -rf Application

run: all
	./Application
