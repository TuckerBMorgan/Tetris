#include "Engine.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>


bool Engine::init() {

    //start up SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not init %s\n", SDL_GetError());
        return false;
    }

    //set how we want the renderer to work
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("Error turning on linear texture filtering\n");
        return false;
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
        return false;
    }
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xF0, 0xFF, 0xFF);

    int imgFlags = IMG_INIT_PNG;

    //Init our image loading libs
    if(!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_Image could not initialize! SDL_Image Error %s\n", IMG_GetError());
        return false;
    }

    //init our audio with a 44100 sample rate
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Audio did not init\n");
        return false;
    }

    //init our text rendering libs
    if(TTF_Init() < 0) {
        printf("Error initing TTF %s", TTF_GetError());
        return false;
    }

    //Load our font we are using
    TTF_Font* font = TTF_OpenFont("resources/raleway.ttf", 28);
	if(font == NULL) {
		printf("Error creating the text font texture %s", TTF_GetError());
        return false;
	}

	SDL_Color text_color;
	text_color.r = 255;
	text_color.g = 255;
	text_color.b = 255;

    //we are initing ten textures for each of the digits 
    //this way we dont have to create a new texture each time update the score
    //we just have to change which digit we are rendering in each position
    char* digit[10] ={"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    for(int i = 0;i<10;i++) {
    	SDL_Surface* text_surface = TTF_RenderText_Solid(font, digit[i], text_color);
	    digits[i] = SDL_CreateTextureFromSurface(this->renderer, text_surface);
    }

    text_color.r = 100;
    text_color.g = 100;
    SDL_Surface* score_surface = TTF_RenderText_Solid(font, "Score:", text_color);
    score_text = SDL_CreateTextureFromSurface(this->renderer, score_surface);    

    text_color.r = 255;
    text_color.g = 0;
    text_color.b = 0;
    SDL_Surface* level_surface = TTF_RenderText_Solid(font, "Level:", text_color);
    level_text = SDL_CreateTextureFromSurface(this->renderer, level_surface);

    text_color.r = 255;
    text_color.g = 0;
    text_color.b = 0;
    SDL_Surface* row_surface = TTF_RenderText_Solid(font, "Cleared Rows:", text_color);
    row_text = SDL_CreateTextureFromSurface(this->renderer, row_surface);

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
    //Set the clear color and clear the frame
    SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(this->renderer);
}

void Engine::renderScore(int score) {
    SDL_Rect render_quad = {15, 15, 3.75 * 15, 20};
    SDL_Color black;
    black.r = 0;
    black.g = 0;
    black.b = 0;

    //render the text
    SDL_RenderCopy(this->renderer, this->score_text, NULL, &render_quad);
    SDL_Rect digit_quad = {150, 30, 15, 30};
    //then the actual score
    for(int i = 0;i<10;i++) {
        int digit = score % 10;
        score = score / 10;
        //we are moving from right to left rendering one digit at a time
        SDL_RenderCopy(this->renderer, this->digits[digit], NULL, &digit_quad);
        digit_quad.x -= 15;
    }
}

void Engine::renderLevel(int level) {
    SDL_Rect on_the_right = {SCREEN_WIDTH * .80, 15, 3.75 * 15, 20};
    SDL_RenderCopy(this->renderer, this->level_text, NULL, &on_the_right);
    SDL_Rect below = {SCREEN_WIDTH * .80, 30, 15, 30};
    if(level > 9) {
        level = 9;//Dont have a way a of rendering over one digit at the moment
        //TODO: Tucker
    }
    SDL_RenderCopy(this->renderer, this->digits[level], NULL, &below);    
}

void Engine::renderRows(int rows) {
    SDL_Rect on_the_right = {15, 75, 10 * 15, 20};
    SDL_RenderCopy(this->renderer, this->row_text, NULL, &on_the_right);

    SDL_Rect below = {150, 90, 15, 30};
    while(rows > 0) {
        int digit = rows % 10;
        SDL_RenderCopy(this->renderer, this->digits[digit], NULL, &below);
        below.x -= 15;
        rows = rows / 10;
    }
}

void Engine::render() {
    SDL_RenderPresent( this->renderer );
}

SDL_Renderer* Engine::getRenderer() {
    return this->renderer;
}