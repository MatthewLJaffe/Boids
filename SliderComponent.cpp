#include "SliderComponent.hpp"

SliderComponent::SliderComponent(std::string name, float minValaue, float maxValue, float startValue, float minX, float maxX, TextComponent* nameText, TextComponent* amountText, SpriteComponent* knobSprite)
{
	this->_nameText = nameText;
	this->_valueText = amountText;
	this->_knobSprite = knobSprite;
	this->_name = name;
	this->_minValue = minValaue;
	this->_maxValue = maxValue;
	this->_value = startValue;
	this->_minX = minX;
	this->_maxX = maxX;
	this->_knobRadius = 8;
	this->_lastMouseX = 0;
	this->_defaultValue = startValue;
}

SliderComponent::SliderComponent(std::string name, float minValaue, float maxValue, float startValue, float minX, float maxX, TextComponent* nameText, TextComponent* amountText, SpriteComponent* knobSprite, bool round)
{
	this->_nameText = nameText;
	this->_valueText = amountText;
	this->_knobSprite = knobSprite;
	this->_name = name;
	this->_minValue = minValaue;
	this->_maxValue = maxValue;
	this->_value = startValue;
	this->_minX = minX;
	this->_maxX = maxX;
	this->_knobRadius = 8;
	this->_lastMouseX = 0;
	this->_defaultValue = startValue;
	this->_round = round;
}

void SliderComponent::init()
{
	_barSprite = &entity->getComponent<SpriteComponent>();
	this->_pos = _barSprite->pos;
	updateValueText(std::to_string(_value));
	float knobX = utils::lerp(_minX, _maxX, (_value - _minValue) / (_maxValue - _minValue));
	_knobSprite->pos.x = knobX;
	onValueUpdate();
}

void SliderComponent::resetValue()
{
	_value = _defaultValue;
	updateValueText(std::to_string(_value));
	float knobX = utils::lerp(_minX, _maxX, (_value - _minValue) / (_maxValue - _minValue));
	_knobSprite->pos.x = knobX;
}

void SliderComponent::updateValueText(std::string message)
{
	std::string amountStr = message;
	if (_round)
		amountStr = amountStr.substr(0, amountStr.find('.'));
	else
		amountStr = amountStr.substr(0, amountStr.find('.') + 3);
	_valueText->setText(amountStr);
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
	InputManager::Instance().buttonPressed = true;
	float newSpriteX = _knobSprite->pos.x + (InputManager::Instance().getMousePos().x - _lastMouseX);
	if (newSpriteX > _maxX)
		newSpriteX = _maxX;
	if (newSpriteX < _minX)
		newSpriteX = _minX;
	if (!_round)
	{
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
	//round value
	else
	{
		float newValue = utils::lerp(_minValue, _maxValue, (newSpriteX - _minX) / (_maxX - _minX));
		if (abs(newValue - _value) >= 1)
		{
			newValue = utils::roundFloat(newValue);
			_knobSprite->pos.x = utils::lerp(_minX, _maxX, (newValue - _minValue) / (_maxValue - _minValue));
			_value = newValue;
			updateValueText(std::to_string(_value));
			onValueUpdate();
			_lastMouseX = InputManager::Instance().getMousePos().x;
		}
	}
}

void SliderComponent::setPos(Vector2 newPos)
{
	Vector2 posDiff = newPos - _pos;
	_minX += posDiff.x;
	_maxX += posDiff.x;
	_barSprite->pos += posDiff;
	_pos = newPos;
	_knobSprite->pos += posDiff;
	_valueText->pos += posDiff;
	_nameText->pos += posDiff;
}

Vector2 SliderComponent::getPos()
{
	return _pos;
}

void SliderComponent::onValueUpdate()
{

}