#include "WorldSpriteComponent.hpp"
Vector2 WorldSpriteComponent::worldOffset = Vector2(0, 0);

WorldSpriteComponent::WorldSpriteComponent(SDL_Texture* tex)
{
	this->sprite = tex;
	_srcRect.x = 0;
	_srcRect.y = 0;
	_screenCenter.x = RenderWindow::WIDTH / 2.0f;
	_screenCenter.y = RenderWindow::HEIGHT/ 2.0f;
	SDL_QueryTexture(sprite, NULL, NULL, &_srcRect.w, &_srcRect.h);
}

void WorldSpriteComponent::init()
{
	transform = &entity->getComponent<TransformComponent>();
}

void WorldSpriteComponent::update()
{
	_destRect.w = utils::roundFloat(_srcRect.w * transform->scale.x);
	_destRect.h = utils::roundFloat(_srcRect.h * transform->scale.y);
	_destRect.x = utils::roundFloat(transform->pos.x + _screenCenter.x + worldOffset.x - _destRect.w / 2.0);
	_destRect.y = utils::roundFloat(transform->pos.y + _screenCenter.y + worldOffset.y - _destRect.h / 2.0);
}

void WorldSpriteComponent::render()
{
	RenderWindow::Instance().render(sprite, _srcRect, _destRect, transform->angle);
}