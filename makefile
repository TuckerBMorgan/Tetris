#OBJS specifies which files to compile as part of the project 
OBJS = ./src/*.cpp 

#CC specifies which compiler we're using 
CC = g++
NVCC = nvcc

DEBUG = -ggdb

STD = -std=c++11

#INCLUDE_PATHS specifies the additional include paths we'll need mixer
INCLUDE_PATHS = -IC:.\deps\SDL\include\SDL2 -IC:.\deps\SDLImage\include\SDL2 -IC:.\deps\SDLMixer\include\SDL2 -IC:.\deps\SDLTTF\include\SDL2 -ID:.\src\*.h

#LIBRARY_PATHS specifies the additional library paths we'll need 
LIBRARY_PATHS = -LC:.\deps\SDL\lib -LC:.\deps\SDLImage\lib -LC:.\deps\SDLMixer\lib -LC:.\deps\SDLTTF\lib

#COMPILER_FLAGS specifies the additional compilation options we're using 
# -w suppresses all warnings 
# -Wl,-subsystem,windows gets rid of the console window 
COMPILER_FLAGS = -w -W -isystem windows

#LINKER_FLAGS specifies the libraries we're linking against 
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

#this is to avoid having to include MinGw libs with every executable
STATIC_LINK_FLAGS = -static-libgcc -static-libstdc++

#OBJ_NAME specifies the name of our exectuable 
OBJ_NAME = tetris
#This is the target that compiles our executable 
release : $(OBJS)
		$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(STATIC_LINK_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

debug : $(OBJS)
		$(CC) $(OBJS) $(DEBUG) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(STATIC_LINK_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

gpu : $(OBJS)
		$(NVCC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(STATIC_LINK_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)