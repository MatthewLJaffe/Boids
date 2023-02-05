#pragma once
#include"TransformComponent.hpp"
#include "RenderWindow.hpp"
#include "Utils.hpp"
#include <SDL.h>

class WorldSpriteComponent : public Component
{
public:
	WorldSpriteComponent(SDL_Texture* tex);
	SDL_Texture* sprite;
	void init() override;
	void render() override;
	void update() override;
	static Vector2 worldOffset;
private:
	TransformComponent* transform;
	SDL_Rect _srcRect;
	SDL_Rect _destRect;
	Vector2 _screenCenter;
};