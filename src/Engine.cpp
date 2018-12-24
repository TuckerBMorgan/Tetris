#include "Engine.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>


bool Engine::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not init %s", SDL_GetError());
        return false;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("Error turning on linear texture filtering");
    }

    this->gWindow = SDL_CreateWindow( "Tetris", 
                                       SDL_WINDOWPOS_UNDEFINED, 
                                       SDL_WINDOWPOS_UNDEFINED, 
                                       SCREEN_WIDTH, SCREEN_HEIGHT,
                                       SDL_WINDOW_SHOWN );

    if(this->gWindow == NULL) {
        return false;
    }

    this->gRenderer = SDL_CreateRenderer(this->gWindow, -1, SDL_RENDERER_ACCELERATED);

    if(this->gRenderer == NULL) {
        printf("The renderer did not init, %s\n", SDL_GetError());
    }
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int imgFlags = IMG_INIT_PNG;

    if(!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_Image could not initialize! SDL_Image Error %s\n", IMG_GetError());
        return false;
    }

    return true;
};

bool Engine::loadMedia() {
    return true;
};

SDL_Texture* Engine::loadTexture(std::string path) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        return NULL;
    }

    newTexture = SDL_CreateTextureFromSurface(this->gRenderer, loadedSurface);
    if(newTexture == NULL) {
        printf("Unable to create texture from %s SDL Error: %s\n", path.c_str(), SDL_GetError());
        SDL_FreeSurface(loadedSurface);
        return NULL;
    }

    return newTexture;
};

void Engine::render() {
    SDL_SetRenderDrawColor(this->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(this->gRenderer);

    SDL_Rect fillRect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    SDL_SetRenderDrawColor(this->gRenderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(this->gRenderer, &fillRect);

    SDL_RenderPresent(this->gRenderer);
}

void Engine::close() {
    SDL_DestroyRenderer(this->gRenderer);
    SDL_DestroyWindow(this->gWindow);
    this->gWindow = NULL;
    this->gRenderer = NULL;

    IMG_Quit();
    SDL_Quit();
};