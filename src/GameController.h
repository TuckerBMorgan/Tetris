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

        //two varibles used in the timing of the frames
        int frame_timer;
        int frame_count;
        
        //higher the level the faster the game moves
        int level;
        int previous_level;
        int direction;

        //applies rules, and handles inputs, does not do timing
        TetrisBoard* board;

        //control varible for if the game is over
        bool quit;

        //Rendering code
        Engine* engine;
        //Music Code
        MusicEngine* music_engine;
        //The board shown 
        Texture* render_board[BOARD_HEIGHT][BOARD_WIDTH];

        //Current action to give to the TetrisBoard
        TetrisAction action;
        //Input
        SDL_Event e;
};