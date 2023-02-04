#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_TTF.h>
#include "RenderWindow.hpp"
#include <string>
#include <vector>

class Assets
{
public:
	Assets(const Assets&) = delete;
	static Assets& Instance();
	void loadAssets();
	void loadImages();
	void loadFonts();
	void closeFonts();
	SDL_Texture* testSprite;
	SDL_Texture* triangleSprite;
	SDL_Texture* triangleSpriteGreen;
	SDL_Texture* triangleSpriteYellow;
	SDL_Texture* green;
	SDL_Texture* predatorSprite;
	SDL_Texture* foodSprite;
	SDL_Texture* boundarySprite;
	SDL_Texture* sliderSprite;
	SDL_Texture* knobSprite;

	TTF_Font* font;

private:
	Assets();
};