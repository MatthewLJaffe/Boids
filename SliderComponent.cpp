#include "SliderComponent.hpp"

SliderComponent::SliderComponent(std::string name, float minValaue, float maxValue, float startValue, float minX, float maxX)
{
	this->_name = name;
	this->_minValue = minValaue;
	this->_maxValue = maxValue;
	this->_value = startValue;
	this->_minX = minX;
	this->_maxX = maxX;
	this->_knobRadius = 8;
	this->_lastMouseX = 0;
	_amountTextOffset = Vector2(40, -10);
	_nameTextOffset = Vector2(-140, -10);
	SDL_Surface* textSurf = TTF_RenderText_Solid(Assets::Instance().font, name.c_str(), {255, 255, 255});
	nameText = RenderWindow::Instance().createFontTexture(textSurf);
	nameSrc = { 0, 0, textSurf->w, textSurf->h };
	SDL_FreeSurface(textSurf);
	std::string amountStr = std::to_string(startValue);
	amountStr = amountStr.substr(0, amountStr.find('.') + 3);
	textSurf = TTF_RenderText_Solid(Assets::Instance().font, amountStr.c_str(), {255, 255, 255});
	amountText = RenderWindow::Instance().createFontTexture(textSurf);
	amountSrc = { 0, 0, textSurf->w, textSurf->h };
	SDL_FreeSurface(textSurf);
}

void SliderComponent::updateValueText(std::string message)
{
	std::string amountStr = message;
	amountStr = amountStr.substr(0, amountStr.find('.') + 3);

	SDL_Surface* textSurf = TTF_RenderText_Solid(Assets::Instance().font, amountStr.c_str(), { 255, 255, 255 });
	SDL_DestroyTexture(amountText);
	amountText = RenderWindow::Instance().createFontTexture(textSurf);
	amountSrc = { 0, 0, textSurf->w, textSurf->h};
	SDL_FreeSurface(textSurf);
}

void SliderComponent::init()
{
	_knobSprite = &entity->getComponent<SpriteComponent>();
	float knobSpriteX = utils::lerp(_minX, _maxX, (_value - _minValue) / (_maxValue - _minValue));
	_knobSprite->pos.x = knobSpriteX;
}

void SliderComponent::update()
{
	if (InputManager::Instance().getMousePressed())
	{
		if (InputManager::Instance().getMousePos().distance(_knobSprite->pos + Vector2(_knobRadius, _knobRadius)) < _knobRadius)
		{
			_sliderMove = true;
			_lastMouseX = InputManager::Instance().getMousePos().x;
		}
	}
	if (InputManager::Instance().getMouseReleased())
	{
		_sliderMove = false;
	}
	if (!_sliderMove) return;
	float newSpriteX = _knobSprite->pos.x + (InputManager::Instance().getMousePos().x - _lastMouseX);
	if (newSpriteX > _maxX)
		newSpriteX = _maxX;
	if (newSpriteX < _minX)
		newSpriteX = _minX;
	_knobSprite->pos.x = newSpriteX;
	float newValue = utils::lerp(_minValue, _maxValue, (newSpriteX - _minX) / (_maxX - _minX));
	if (abs(newValue - _value) > .0001)
	{
		_value = newValue;
		updateValueText(std::to_string(_value));
		onValueUpdate();
	}
	_lastMouseX = InputManager::Instance().getMousePos().x;
}

void SliderComponent::render()
{
	nameDst.x = _minX + _nameTextOffset.x;
	nameDst.y = _knobSprite->pos.y + _nameTextOffset.y;
	nameDst.w = nameSrc.w;
	nameDst.h = nameSrc.h;
	RenderWindow::Instance().render(nameText, nameSrc, nameDst, 0);
	amountDst.x = _maxX + _amountTextOffset.x;
	amountDst.y = _knobSprite->pos.y + _amountTextOffset.y;
	amountDst.w = amountSrc.w;
	amountDst.h = amountSrc.h;
	RenderWindow::Instance().render(amountText, amountSrc, amountDst, 0);
}

void SliderComponent::onValueUpdate()
{

}