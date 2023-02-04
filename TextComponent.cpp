#include "TextComponent.hpp"

TextComponent::TextComponent(std::string message, Vector2 pos, float scale, int fontSize, TTF_Font* font, SDL_Color color)
{
	this->pos = pos;
	this->scale = scale;
	this->_fontSize = fontSize;
	this->_font = font;
	this->_color = color;
	TTF_SetFontSize(font, fontSize);
	SDL_Surface* textSurf = TTF_RenderText_Solid(font, message.c_str(), color);
	_tex = RenderWindow::Instance().createFontTexture(textSurf);
	_srcRect = { 0, 0, textSurf->w, textSurf->h };
	SDL_FreeSurface(textSurf);
}

void TextComponent::setText(std::string message)
{
	SDL_DestroyTexture(_tex);
	TTF_SetFontSize(_font, _fontSize);
	SDL_Surface* textSurf = TTF_RenderText_Solid(_font, message.c_str(), _color);
	_tex = RenderWindow::Instance().createFontTexture(textSurf);
	_srcRect = { 0, 0, textSurf->w, textSurf->h };
	SDL_FreeSurface(textSurf);
}