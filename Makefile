CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -pedantic -g
INCLUDES = -I$(SFML_PATH)\include

SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

ifeq ($(OS),Windows_NT)
	EXECUTABLE = chess.exe
	LIBS = $(SFML_PATH)\lib\libsfml-graphics.a $(SFML_PATH)\lib\libsfml-window.a $(SFML_PATH)\lib\libsfml-system.a $(SFML_PATH)\lib\libsfml-audio.a -lopengl32
else
	EXECUTABLE = chess
	LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lGL
endif

.PHONY: all clean

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
