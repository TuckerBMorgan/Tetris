#include <windows.h>
#include "GameController.h"

bool GameController::init() {
    this->frame_count = 0;
    this->frame_timer = 100;
    this->previous_level = 1;
    this->quit = false;
    this->previous_level = 1;

    //Init SDL, Rendering stuff
    this->engine = new Engine();
    if(this->engine->init() == false) {
        printf("Engine was able to init\n");
        return false;
    }

    //init the music engine
    this->music_engine = new MusicEngine();
    this->music_engine->init();
	SongId index = this->music_engine->loadSong("resources/Tetris.mp3");
	this->music_engine->playMusic(index);

    //the place that handels most of the game rules, related to the 
    //tetris board itself
    this->board = new TetrisBoard();
    this->board->init();

    //the level sets score multiplyer and drop rate
    this->level = 1;

    //this is for moving and rotation, -1 is left, 1 is right...kinda
    this->direction = 0;


    //init our board pieces, we never have to create new ones
    //we simply change the color of a particular piece on the board
    //This keeps memory and preformance constant
	for(int y = 0;y<28;y++){
		for(int x = 0;x<10;x++)
		{
			this->render_board[y][x] = new Texture();
			this->render_board[y][x]->loadFromFile("resources/block.png", engine);
			this->render_board[y][x]->setScale(0.25);
			this->render_board[y][x]->setColor(Color{50, 50, 50});
			this->render_board[y][x]->setAlpha(255);
			this->render_board[y][x]->render((SCREEN_WIDTH / 2 - 70) + x * 15, (SCREEN_HEIGHT / 2 + 150) - y * 15, engine);
		}
	}

    for(int y = 0;y<4;y++) {
        for(int x = 0;x<4;x++) {
            this->next_cluster_display[y][x] = new Texture();
            this->next_cluster_display[y][x]->loadFromFile("resources/block.png", engine);
            this->next_cluster_display[y][x]->setScale(0.25);
            this->next_cluster_display[y][x]->setColor(Color{50, 50, 50});
            this->next_cluster_display[y][x]->setAlpha(255);
            this->next_cluster_display[y][x]->render(SCREEN_WIDTH * .80, SCREEN_HEIGHT * .30, engine);
        }
    }

    this->engine->render();
    return true;
}

void GameController::handleInput() {
    while(SDL_PollEvent(&e) != 0) {
        if(this->e.type == SDL_QUIT) {
            this->quit = true;
        }
        else if(this->e.type == SDL_KEYDOWN) {
            switch(this->e.key.keysym.sym) {
                case SDLK_DOWN:
                    this->action = TetrisAction::Drop;
                break;

                case SDLK_LEFT:
                    this->action = TetrisAction::Move;
                    this->direction = -1;
                break;

                case SDLK_RIGHT:
                    this->action = TetrisAction::Move;
                    this->direction = 1;
                break;

                case SDLK_q:
                    this->action = TetrisAction::Rotate;
                    this->direction = -1;
                break;

                case SDLK_e:
                    this->action = TetrisAction::Rotate;
                    this->direction = 1;
                break;

                case SDLK_p:
                    if(this->music_engine->getIsPlaying()) {
                        this->music_engine->pauseCurrentMusic();
                    }
                    else {
                        this->music_engine->resumeMusic();
                    }
                break;

                default:
                this->action = TetrisAction::Fall;
                break;
            }
        }
    }
}

void GameController::update() {
    while(!this->quit) {
        direction = 0;
        this->handleInput();
        //we have the || clause to allow for us to keep doing the update
        //At the end we make sure to reset the counter only on falls, 
        //so that way rotations, and moves keep the timer going
        if(this->frame_count == this->frame_timer || this->action != TetrisAction::Fall) {
            
            //first we have the board execute the actions
            this->board->update(this->action, this->direction);
            

            //after this it is all rendering
            this->engine->setupFrame();
            //handle the UI, score and level
            this->engine->renderScore(this->board->getScore());
            this->engine->renderLevel(this->board->getLevel());
            this->engine->renderRows(this->board->getClearedRows());

            //go through each of the indexes
            for(int y = 0;y < BOARD_HEIGHT;y++) {
                for(int x = 0;x < BOARD_WIDTH;x++) {
                    if(this->board->getIndex(x, y) == TetrisClusterType::None) {
                        //if the piece is not an active cluster, render it gray
                        this->render_board[y][x]->setColor(Color{50, 50, 50});
                    } else {
                        //else find the color of the cluster, and render the block as that
						int color_choice = (int)this->board->getIndex(x, y) - 1;
						this->render_board[y][x]->setColor(BLOCK_COLORS[color_choice]);
                    }
                    this->render_board[y][x]->render((SCREEN_WIDTH / 2 - 70) + x * 15, (SCREEN_HEIGHT / 2 + 150) - y * 15, engine);
                }
            }
            for(int y = 0;y<4;y++) {
                for(int x = 0;x<4;x++) {
                    this->next_cluster_display[y][x]->setColor(Color{50, 50, 50});
                }
            }

            TetrisCluster next_cluster = this->board->getNextCluster();
            for(int i = 0;i<4;i++) {
                int x_offset = next_cluster.blocks[i].offset_x;
                int y_offset = next_cluster.blocks[i].offset_y;
                Color color = BLOCK_COLORS[(int)next_cluster.tetris_cluster_type - 1];
                this->next_cluster_display[2 + y_offset][1 + x_offset]->setColor(color);
            }
            for(int y = 0;y<4;y++) {
                for(int x = 0;x<4;x++) {
                    this->next_cluster_display[y][x]->render(SCREEN_WIDTH * .80 + (x * 15), SCREEN_HEIGHT * .30 + (y * 15), engine);
                }
            }

            //present our frame!
            this->engine->render();
            if(this->frame_count == this->frame_timer) {
                this->frame_count = 0;
            }
        }
        else {
            this->frame_count += 1;
        }

        //Check if we have gone up in level
        int new_level = this->board->getLevel();
        if(new_level != this->previous_level) {
            //reduce the drop frame amount
            this->frame_count = 0;
            this->frame_timer = 100 - ((new_level - 1) * 10 );
            if(frame_timer < 10) {
                frame_timer = 10;
            }
            this->previous_level = new_level;
        }

        this->action = TetrisAction::Fall;
        Sleep(1);
    }
}