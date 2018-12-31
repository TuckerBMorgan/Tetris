#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 640;


class Engine {
    public:
        bool init();
        void setupFrame();
        void render();
        SDL_Renderer* getRenderer();
        void renderScore(int score);
        void renderLevel(int level);

        //Loads individual image as texture
        SDL_Texture* loadTexture(std::string path);
        
    private:
    
        //The window we'll be rendering to
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* viewport_texture;
        SDL_Texture* score_text;
        SDL_Texture* level_text;
        SDL_Texture* cleared_text;
        SDL_Texture* digits[10];
};