#include "Engine.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>


bool Engine::init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not init %s\n", SDL_GetError());
        return false;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("Error turning on linear texture filtering\n");
    }

    this->window = SDL_CreateWindow( "Tetris", 
                                       SDL_WINDOWPOS_UNDEFINED, 
                                       SDL_WINDOWPOS_UNDEFINED, 
                                       SCREEN_WIDTH, SCREEN_HEIGHT,
                                       SDL_WINDOW_SHOWN );

    if(this->window == NULL) {
        printf("The window could not init\n");
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

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Audio did not init\n");
        return false;
    }
    if(TTF_Init() < 0) {
        printf("Error initing TTF %s", TTF_GetError());
        return false;
    }
    TTF_Font* font = TTF_OpenFont("resources/raleway.ttf", 28);
	if(font == NULL) {
		printf("Error creating the text font texture %s", TTF_GetError());
        return false;
	}

	SDL_Color text_color;
	text_color.r = 255;
	text_color.g = 255;
	text_color.b = 255;

    char* digit[10] ={"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    for(int i = 0;i<10;i++) {
    	SDL_Surface* text_surface = TTF_RenderText_Solid(font, digit[i], text_color);
	    digits[i] = SDL_CreateTextureFromSurface(this->renderer, text_surface);
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

    SDL_Rect topLeftViewPort;
    topLeftViewPort.x = 0;
    topLeftViewPort.y = 0;
    topLeftViewPort.w = SCREEN_WIDTH;
    topLeftViewPort.h = SCREEN_HEIGHT;
    SDL_RenderSetViewport(this->renderer, &topLeftViewPort); 
}

void Engine::render() {
    SDL_Rect renderQuad = {10, 10, 15, 30};
    for(int i = 0;i<10;i++) {
        SDL_RenderCopy(this->renderer, this->digits[i], NULL, &renderQuad);
        renderQuad.x += 15;
    }
//    SDL_RenderCopy(this->renderer, this->text_texture, NULL, &renderQuad);
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