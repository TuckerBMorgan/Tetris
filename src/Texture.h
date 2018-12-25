#pragma once
#include <SDL.h>
#include <string>
#include "Util.h"

class Engine;

class Texture {
    public:
        Texture();
        ~Texture();

        bool loadFromFile(std::string path, Engine* engine);
        void free();
        void render(int x, int y, Engine* engine);
        int getWidth();
        int getHeight();
        void setScale(float s);
        void setColor(Color color);
        void setAlpha(uint8_t a);

    private:
        SDL_Texture* texture;
        int width;
        int height;
        float scale;
        Color color;
};