#pragma once
#include "Texture.h"
#include "TetrisBoard.h"
#include "Engine.h"
#include "MusicEngine.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 28

class GameController {
    public:
        bool init();
        void update();

    private:
        
        void handleInput();

        int frame_timer;
        int frame_count;
        int level;
        int direction;
        TetrisBoard* board;
        bool quit;
        Engine* engine;
        MusicEngine* music_engine;
        Texture* render_board[BOARD_HEIGHT][BOARD_WIDTH];

        TetrisAction action;
        SDL_Event e;
};