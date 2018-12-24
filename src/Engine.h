#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


class Engine {
    public:
        bool init();
        bool loadMedia();
        void close();
        void render();

        //Loads individual image as texture
        SDL_Texture* loadTexture( std::string path );

    private:
    
        //The window we'll be rendering to
        SDL_Window* gWindow;
        //The window renderer
        SDL_Renderer* gRenderer;



};