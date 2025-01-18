#include <iostream>
#include <cstdio>
#include <SDL.h>

const int WIDTH = 640;
const int HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Window* window = nullptr;
SDL_Surface* screenSurface = nullptr; // an image data type. uses CPU to render.
SDL_Surface* someImage = nullptr;


bool init(){
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else {
        window = SDL_CreateWindow("SDL pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
                                  SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            screenSurface = SDL_GetWindowSurface(window);
        }
    }

    return success;
}

bool loadMedia(){
    bool success = true;

    someImage = SDL_LoadBMP("D:\\C++\\projects\\GameTBD\\assets\\nathan-lorre-decor-culdesac-1.bmp");
    if(someImage == nullptr){
        printf( "Unable to load image %s! SDL Error: %s\n", "D:\\C++\\projects\\GameTBD\\assets\\nathan-lorre-decor-culdesac-1.bmp", SDL_GetError() );
        success = false;
    }
    return success;
}

void close(){
    SDL_FreeSurface(someImage);
    someImage= nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_Quit();
}

int main(int argc,char* argv[]) {

    SDL_Rect imageSize = {0,0,WIDTH,HEIGHT};

    //SDL_Renderer* renderer = nullptr;
    std::cout << "Hello World!" << std::endl;
    std::cout << "Current Working Directory: " << SDL_GetBasePath() << std::endl;

    if(!init()){
        printf( "Failed to initialize!\n" );
    }
    else{
        if(!loadMedia()){
            printf( "Failed to load media!\n" );
        } else{
            //takes a source surface and stamps a copy of it onto the destination surface
            //SDL_BlitSurface(someImage, nullptr,screenSurface, nullptr);
            //for scaling the image to our window // u do not need to actually use the image size u can just as nullptr
            // it uses the default behavior and scales the source surface to fit the entire destination surface.
            SDL_BlitScaled(someImage, nullptr,screenSurface, &imageSize);

            SDL_UpdateWindowSurface(window);
            SDL_Delay(5000);
        }
    }
    close();

    return 0;
}
