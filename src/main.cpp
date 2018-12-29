/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
#include <windows.h>

#include "Engine.h"
#include "MusicEngine.h"
#include "Texture.h"
#include "TetrisBoard.h"

void gameLoop() {

}

int main(int argc, char* args[]) {
	Engine* engine = new Engine();
	
	if (!engine->init()){
		printf("There is this\n");
		return 1;
	}

	if(!engine->loadMedia()) {
		return 1;
	}

	TetrisBoard* tetris_board = new TetrisBoard();
	tetris_board->init();

	TetrisClusterType render_map[28][10];
	for(int y = 0;y<28;y++) {
		for(int x = 0;x<10;x++)	{
			render_map[y][x] = TetrisClusterType::None;
		}
	}
	
	Texture* board[28][10];

	MusicEngine* music_engine = new MusicEngine();
	music_engine->init();
	SongId index = music_engine->loadSong("resources/Tetris.mp3");
	music_engine->playMusic(index);
//	music_engine->playCurrentMusic();
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
	int frame_count = 0;
	int frame_timer = 100;
	TetrisAction action;

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
						action = TetrisAction::Drop;
						//Come back to this
					break;

					case SDLK_LEFT:
						action = TetrisAction::Move;
						direction = -1;
					break;

					case SDLK_RIGHT:
						action = TetrisAction::Move;
						direction = 1;
					break;

					case SDLK_q:
						action = TetrisAction::Rotate;
						direction = -1;
					break;

					case SDLK_e:
						action = TetrisAction::Rotate;
						direction = 1;
					break;

					case SDLK_p:
						if(music_engine->getIsPlaying()) {
							music_engine->pauseCurrentMusic();
						}
						else {
							music_engine->resumeMusic();
						}

					break;

					default:
					action = TetrisAction::Fall;
					break;
				}
			}
		}
		if(frame_count == frame_timer || action != Fall) {
			tetris_board->update(action, direction);
			engine->setupFrame();
			for(int y = 0;y<28;y++)
			{
				for(int x = 0;x<10;x++) {
					if(render_map[y][x] != tetris_board->getIndex(x, y)) {
						//we only want to render what we have to
						//so this will diff the last board and new one from TetriSBoard
						//and update things as needed
						if(tetris_board->getIndex(x, y) == TetrisClusterType::None) {
							//set alpha to zero and rerender
							board[y][x]->setColor(Color{50, 50, 50});
						}
						else {
							//set alpha and color, rerender
							int color_choice = (int)tetris_board->getIndex(x, y) - 1;
							board[y][x]->setColor(BLOCK_COLORS[color_choice]);
						}
						board[y][x]->render((SCREEN_WIDTH / 2 - 70) + x * 15, (SCREEN_HEIGHT / 2 + 150) - y * 15, engine);
						render_map[y][x] = tetris_board->getIndex(x, y);
					}
				}
			}
			engine->render();
			frame_count = 0;
		}
		else {
			frame_count += 1;
		}

		action = Fall;
		Sleep(1);
	}
	engine->close();


	return 0;
}