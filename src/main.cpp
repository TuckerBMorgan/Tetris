/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
#include <windows.h>

#include "Engine.h"
#include "Texture.h"
#include "TetrisBoard.h"

int main(int argc, char* args[]) {
	Engine* engine = new Engine();
	TetrisBoard* tetrisBoard = new TetrisBoard();
	tetrisBoard->init();

	TetrisClusterType renderMap[28][10];
	for(int y = 0;y<28;y++) {
		for(int x = 0;x<10;x++)	{
			renderMap[y][x] = TetrisClusterType::None;
		}
	}
	
	if (!engine->init()){
		return 1;
	}

	if(!engine->loadMedia()) {
		return 1;
	}
	
	Texture* board[28][10];

	engine->setupFrame();
	for(int y = 0;y<28;y++){
		for(int x = 0;x<10;x++)
		{
			board[y][x] = new Texture();
			board[y][x]->loadFromFile("resources/block.png", engine);
			board[y][x]->setScale(0.25);
			board[y][x]->setColor(Color{50, 50, 50});
			board[y][x]->setAlpha(255);
			board[y][x]->render((SCREEN_WIDTH / 2 - 70) + x * 15, (SCREEN_HEIGHT / 2 + 150) - y * 15, engine);
		}
	}
	engine->render();

	bool markedDirty = true;
	bool quit = false;
	SDL_Event e;
	int direction = 0;
	while(!quit) {
		direction = 0;
		while(SDL_PollEvent(&e) != 0) {
			if(e.type == SDL_QUIT) {
				quit = true;
			}
			else if( e.type == SDL_KEYDOWN ) {
				switch( e.key.keysym.sym )
				{
					case SDLK_DOWN:
						//Come back to this
					break;

					case SDLK_LEFT:
						direction = -1;
					break;

					case SDLK_RIGHT:
						direction = 1;
					break;

					default:
					break;
				}
			}
		}

		markedDirty = tetrisBoard->update(direction);

		if(markedDirty) {
			engine->setupFrame();
			for(int y = 0;y<28;y++)
			{
				for(int x = 0;x<10;x++) {
					if(renderMap[y][x] != tetrisBoard->getIndex(x, y)) {
						//we only want to render what we have to
						//so this will diff the last board and new one from TetriSBoard
						//and update things as needed
						if(tetrisBoard->getIndex(x, y) == TetrisClusterType::None) {
							//set alpha to zero and rerender
							board[y][x]->setColor(Color{50, 50, 50});
						}
						else {
							//set alpha and color, rerender
							board[y][x]->setAlpha(255);
							int color_choice = (int)tetrisBoard->getIndex(x, y) - 1;
							board[y][x]->setColor(BLOCK_COLORS[color_choice]);
						}
						board[y][x]->render((SCREEN_WIDTH / 2 - 70) + x * 15, (SCREEN_HEIGHT / 2 + 150) - y * 15, engine);
						renderMap[y][x] = tetrisBoard->getIndex(x, y);
					}
				}
			}
			engine->render();
			markedDirty = false;
		}
		Sleep(64);
	}
	engine->close();


	return 0;
}