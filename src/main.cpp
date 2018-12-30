/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
#include <windows.h>

#include "GameController.h"

#include "Engine.h"
#include "MusicEngine.h"
#include "Texture.h"
#include "TetrisBoard.h"

int main(int argc, char* args[]) {


	GameController* game_controller = new GameController();
	if(!game_controller->init()) {
		printf("Was unable to init game_controller\n");
		return 0;
	}
	game_controller->update();
	return 0;
}