#pragma once
#include "ECS.hpp"
#include "Vector2.hpp"
#include <SDL.h>
#include "RenderWindow.hpp"
#include "Utils.hpp"


class SpriteComponent : public Component
{
public:
	Vector2 pos;
	float scale;
	SpriteComponent(Vector2 pos, float scale, SDL_Texture* tex);
	void render() override;
	void update() override;
	Vector2 getSize();
	void setSprite(SDL_Texture* newTex);

protected:
	SDL_Texture* _tex;
	SDL_Rect _srcRect;
	SDL_Rect _destRect;
	SpriteComponent() 
	{
		scale = 1;
		_srcRect = {0,0,0,0};
		_destRect = {0,0,0,0};
		_tex = nullptr;
	}

	
};