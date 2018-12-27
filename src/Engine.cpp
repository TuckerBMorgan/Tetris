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

    this->window = SDL_CreateWindow( "Tetris", 
                                       SDL_WINDOWPOS_UNDEFINED, 
                                       SDL_WINDOWPOS_UNDEFINED, 
                                       SCREEN_WIDTH, SCREEN_HEIGHT,
                                       SDL_WINDOW_SHOWN );

    if(this->window == NULL) {
        return false;
    }

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

    if(this->renderer == NULL) {
        printf("The renderer did not init, %s\n", SDL_GetError());
    }
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xF0, 0xFF, 0xFF);

    int imgFlags = IMG_INIT_PNG;

    if(!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_Image could not initialize! SDL_Image Error %s\n", IMG_GetError());
        return false;
    }

    return true;
};

bool Engine::loadMedia() {

    this->viewport_texture = loadTexture("resources/viewport.png");
    if(this->viewport_texture == NULL) {
        printf("Failed to load viewport image");
        return false;
    }
    return true;
};

SDL_Texture* Engine::loadTexture(std::string path) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        return NULL;
    }

    newTexture = SDL_CreateTextureFromSurface(this->renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    if(newTexture == NULL) {
        printf("Unable to create texture from %s SDL Error: %s\n", path.c_str(), SDL_GetError());
        return NULL;
    }
    return newTexture;
};

void Engine::setupFrame() {
    SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0x00, 0xFF);
  //  SDL_RenderClear(this->renderer);

    SDL_Rect topLeftViewPort;
    topLeftViewPort.x = 0;
    topLeftViewPort.y = 0;
    topLeftViewPort.w = SCREEN_WIDTH;
    topLeftViewPort.h = SCREEN_HEIGHT;
    SDL_RenderSetViewport(this->renderer, &topLeftViewPort); 
}

void Engine::render() {
    SDL_RenderPresent( this->renderer );
}

SDL_Renderer* Engine::getRenderer() {
    return this->renderer;
}

void Engine::close() {
    SDL_DestroyTexture(this->viewport_texture);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    this->window = NULL;
    this->renderer = NULL;
    this->viewport_texture = NULL;

    IMG_Quit();
    SDL_Quit();
};