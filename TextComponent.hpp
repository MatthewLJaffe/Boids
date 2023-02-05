#pragma once
#include "SpriteComponent.hpp"
#include "SDL_ttf.h"

class TextComponent : public SpriteComponent
{
public:
	TextComponent(std::string message, Vector2 pos, float scale, int fontSize, TTF_Font* font, SDL_Color color, bool rightAlign);
	void setText(std::string message);
	void update() override;
private:
	int _fontSize;
	bool _rightAlign = false;
	std::string _message;
	TTF_Font* _font;
	SDL_Color _color;
};