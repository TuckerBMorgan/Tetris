#include "Texture.h"
#include "Engine.h"
#include <SDL.h>
#include <SDL_image.h>


Texture::Texture() {
    this->texture = NULL;
    this->width = 0;
    this->height = 0;
}

Texture::~Texture() {
    free();
}


void Texture::setScale(float s) {
    this->scale = s;
}

void Texture::setColor(Color color) {
    this->color = color;
    SDL_SetTextureColorMod(this->texture, color.r, color.g, color.b);
}

void Texture::setAlpha(uint8_t a) {
    SDL_SetTextureAlphaMod(this->texture, a);
}

void Texture::render(int x, int y, Engine* engine) {
    SDL_Rect renderQuad = {x, y, this->width * this->scale, this->height * this->scale};
    SDL_RenderCopy(engine->getRenderer(), this->texture, NULL, &renderQuad);
}

bool Texture::loadFromFile(std::string path, Engine* engine) {
    free();
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error %s\n", path.c_str(), IMG_GetError());
        return false;
    }

    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

    newTexture = SDL_CreateTextureFromSurface(engine->getRenderer(), loadedSurface);
    if(newTexture == NULL) {
        printf("Unable to creat texture %s SDL Error: %s", path.c_str(), SDL_GetError());
        return false;
    }

    this->width = loadedSurface->w;
    this->height = loadedSurface->h;

    SDL_FreeSurface(loadedSurface);

    this->texture = newTexture;
    this->scale = 1.0;

    Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    this->color = color;
    return this->texture != NULL;

}

void Texture::free() {
    if(this->texture != NULL) {
        SDL_DestroyTexture(this->texture);
        this->texture = NULL;
        this->width = 0;
        this->height = 0;
    }
}