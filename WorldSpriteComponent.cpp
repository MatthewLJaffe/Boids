#include "WorldSpriteComponent.hpp"

WorldSpriteComponent::WorldSpriteComponent(SDL_Texture* tex)
{
	this->sprite = tex;
	_srcRect.x = 0;
	_srcRect.y = 0;
	screenCenter.x = RenderWindow::Instance().WIDTH / 2.0f;
	screenCenter.y = RenderWindow::Instance().HEIGHT/ 2.0f;
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
	_destRect.x = utils::roundFloat(transform->pos.x + screenCenter.x - _destRect.w / 2.0);
	_destRect.y = utils::roundFloat(transform->pos.y + screenCenter.y - _destRect.h / 2.0);
}

void WorldSpriteComponent::render()
{
	RenderWindow::Instance().render(sprite, _srcRect, _destRect, transform->angle);
}

