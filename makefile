#OBJS specifies which files to compile as part of the project 
OBJS = 01_hello_SDL.cpp 
#OBJ_NAME specifies the name of our exectuable 
OBJ_NAME = 01_hello_SDL 
#This is the target that compiles our executable 
all : $(OBJS) g++ $(OBJS) 
					-IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -W -isystem windows -lmingw32 -lSDL2main -lSDL2 -o $(OBJ_NAME)