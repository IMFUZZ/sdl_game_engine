#http://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php
#OBJS specifies which files to compile as part of the project
OBJS = $(wildcard ./src/*.cpp) $(wildcard ./src/game/*.cpp) $(wildcard ./src/game/*.h)  

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I./lib/SDL2_32/include/SDL2

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L./lib/SDL2_32/lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# add '-Wl,-subsystem,windows' to get rid of the console window
COMPILER_FLAGS = -w 

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o ./bin/$(OBJ_NAME)