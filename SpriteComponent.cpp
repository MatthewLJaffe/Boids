#include "SpriteComponent.hpp"


SpriteComponent::SpriteComponent(Vector2 pos, float scale, SDL_Texture* tex)
{
	this->pos = pos;
	this->scale = scale;
	_tex = tex;
	_srcRect.x = 0;
	_srcRect.y = 0;
	SDL_QueryTexture(_tex, NULL, NULL, &_srcRect.w, &_srcRect.h);
	_destRect.x = utils::roundFloat(pos.x * scale);
	_destRect.y = utils::roundFloat(pos.y * scale);
	_destRect.w = utils::roundFloat(_srcRect.w * scale);
	_destRect.h = utils::roundFloat(_srcRect.h * scale);
}

void SpriteComponent::update()
{
	_destRect.x = utils::roundFloat(pos.x * scale);
	_destRect.y = utils::roundFloat(pos.y * scale);
	_destRect.w = utils::roundFloat(_srcRect.w * scale);
	_destRect.h = utils::roundFloat(_srcRect.h * scale);
}

void SpriteComponent::setSprite(SDL_Texture* newTex)
{
	_tex = newTex;
	SDL_QueryTexture(_tex, NULL, NULL, &_srcRect.w, &_srcRect.h);
	_destRect.x = utils::roundFloat(pos.x * scale);
	_destRect.y = utils::roundFloat(pos.y * scale);
	_destRect.w = utils::roundFloat(_srcRect.w * scale);
	_destRect.h = utils::roundFloat(_srcRect.h * scale);
}


void SpriteComponent::render()
{
	RenderWindow::Instance().render(_tex, _srcRect, _destRect, 0.0f);
}

Vector2 SpriteComponent::getSize()
{
	return Vector2(static_cast<float>(_destRect.w), static_cast<float>(_destRect.h));
}