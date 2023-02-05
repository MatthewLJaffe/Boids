#pragma once
#include "SpriteComponent.hpp"
#include "InputManager.hpp"
#include <functional>

class ButtonComponent : public Component
{
public:
	ButtonComponent(SDL_Texture* defaultSprite, SDL_Texture* pressedSprite);
	ButtonComponent(SDL_Texture* defaultSprite, SDL_Texture* pressedSprite, const std::function<void()>& pressedCallback);
	void update() override;
	void init() override;
protected:
	SpriteComponent* _spriteComponent;
	SDL_Texture* _pressedSprite;
	SDL_Texture* _defaultSprite;
	float _width = 0;
	float _height = 0;
	std::function<void()> _pressedCallback = {};
	virtual void onButtonPress();
};