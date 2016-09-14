#http://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php
#OBJS specifies which files to compile as part of the project
OBJS = $(wildcard ./src/*.cpp) $(wildcard ./src/gameEngine/*.cpp) $(wildcard ./src/gameEngine/*.h)  

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
ifeq ($(OS),Windows_NT)
	INCLUDE_PATHS = -I./lib/SDL2_32/include

	#LIBRARY_PATHS specifies the additional library paths we'll need
	LIBRARY_PATHS = -L./lib/SDL2_32/lib 
	
	#LINKER_FLAGS specifies the libraries we're linking against
	LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2
else 
	INCLUDE_PATHS =
	
	LIBRARY_PATHS =
	
	#LINKER_FLAGS specifies the libraries we're linking against
	LINKER_FLAGS = -lSDL2main -lSDL2
endif

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# add '-Wl,-subsystem,windows' to get rid of the console window
COMPILER_FLAGS = -w 

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o ./bin/$(OBJ_NAME)