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

	for(int y = 0;y<28;y++){
		for(int x = 0;x<10;x++)
		{
			board[y][x] = new Texture();
			board[y][x]->loadFromFile("resources/block.png", engine);
			board[y][x]->setScale(0.25);
			board[y][x]->setColor(Color{255, 0, 0});
			board[y][x]->setAlpha(0);
		}
	}
		
	Texture* personTexture = new Texture();
	personTexture->loadFromFile("resources/block.png", engine);
	personTexture->setScale(0.25);
	Texture* backgroundTexture = new Texture();
	backgroundTexture->loadFromFile("resources/background.png", engine);


	bool markedDirty = true;
	bool quit = false;
	SDL_Event e;
	while(!quit) {
		while(SDL_PollEvent(&e) != 0) {
			if(e.type == SDL_QUIT) {
				quit = true;
			}
		} 

		
		markedDirty = tetrisBoard->update();

		if(markedDirty) {
			engine->setupFrame();
		//	backgroundTexture->render(0, 0, engine);
			for(int y = 0;y<28;y++)
			{
				for(int x = 0;x<10;x++) {
					if(renderMap[y][x] != tetrisBoard->getIndex(x, y)) {
						if(tetrisBoard->getIndex(x, y) == TetrisClusterType::None) {
							//set alpha to zero and rerender
							board[x][y]->setColor(Color{128, 128, 128});
						}
						else {
							board[y][x]->setAlpha(255);
							board[y][x]->setColor(BLOCK_COLORS[tetrisBoard->getIndex(x, y) + 1]);
							//set alpha and color, rerender
						}
						board[y][x]->render((SCREEN_WIDTH / 2 - 70) + x * 15, (SCREEN_HEIGHT / 2 + 150) - y * 15, engine);
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