//
// Created by Tuna on 21.01.2025.
//

#ifndef GAMETBD_TEXTURE_H
#define GAMETBD_TEXTURE_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;


class Texture
{
public:
    //Initializes variables
    Texture();

    //Deallocates memory
    ~Texture();

    //Loads image at specified path
    bool loadFromFile( std::string path );

#if defined(SDL_TTF_MAJOR_VERSION)
    //Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
#endif

    //Deallocates texture
    void free();

    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    //Set blending
    void setBlendMode( SDL_BlendMode blending );

    //Set alpha modulation
    void setAlpha( Uint8 alpha );

    //Renders texture at given point
    void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    //Gets image dimensions
    int getWidth();
    int getHeight();

private:
    //The actual hardware texture
    SDL_Texture* texture;

    //Image dimensions
    int width;
    int height;
};


#endif //GAMETBD_TEXTURE_H
