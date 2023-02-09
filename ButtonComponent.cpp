#include "ButtonComponent.hpp"

ButtonComponent::ButtonComponent(SDL_Texture* defaultSprite, SDL_Texture* pressedSprite)
{
	this->_pressedSprite = pressedSprite;
	this->_defaultSprite = defaultSprite;
	_spriteComponent = nullptr;
}

ButtonComponent::ButtonComponent(SDL_Texture* defaultSprite, SDL_Texture* pressedSprite, const std::function<void()>& pressedCallback)
{
	this->_pressedSprite = pressedSprite;
	this->_defaultSprite = defaultSprite;
	this->_pressedCallback = pressedCallback;
}

void ButtonComponent::init()
{
	_spriteComponent = &entity->getComponent<SpriteComponent>();
	_width = _spriteComponent->getSize().x;
	_height = _spriteComponent->getSize().y;
}

void ButtonComponent::update()
{
	if (InputManager::Instance().getMousePressed() &&
		utils::inRect(InputManager::Instance().getMousePos().x, InputManager::Instance().getMousePos().y, _spriteComponent->pos.x, _spriteComponent->pos.y, _width, _height))
	{
		_spriteComponent->setSprite(_pressedSprite);
	}
	else if (InputManager::Instance().getMouseReleased())
	{
		_spriteComponent->setSprite(_defaultSprite);
		if (utils::inRect(InputManager::Instance().getMousePos().x, InputManager::Instance().getMousePos().y, _spriteComponent->pos.x, _spriteComponent->pos.y, _width, _height))
		{
			onButtonPress();
		}
	}
}

void ButtonComponent::onButtonPress()
{
	_pressedCallback();
}