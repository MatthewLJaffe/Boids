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


protected:
	SDL_Texture* _tex;
	SDL_Rect _srcRect;
	SDL_Rect _destRect;
	SpriteComponent() {}

	
};