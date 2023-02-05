#pragma once
#include "ECS.hpp"
#include "SDL_image.h"
#include "SDL_TTF.h"
#include "SpriteComponent.hpp"
#include "TextComponent.hpp"
#include "InputManager.hpp"
#include "Assets.hpp"
#include "Utils.hpp"
#include <cmath>

class SliderComponent : public Component
{
public:
	SliderComponent(std::string name, float minValaue, float maxValue, float startValue, float minX, float maxX, 
		TextComponent* nameText, TextComponent* amountText, SpriteComponent* knobSprite);
	SliderComponent(std::string name, float minValaue, float maxValue, float startValue, float minX, float maxX,
		TextComponent* nameText, TextComponent* amountText, SpriteComponent* knobSprite, bool round);
	void update() override;
	void init() override;
	void setPos(Vector2 newPos);
	Vector2 getPos();
protected:
	void updateValueText(std::string message);
	virtual void onValueUpdate();
	void resetValue();
	float _minValue;
	float _maxValue;
	float _minX;
	float _maxX;
	float _value;
	float _defaultValue;
	float _knobRadius;
	float _lastMouseX;
	bool _sliderMove = false;
	bool _round = false;
	Vector2 _pos;
	TextComponent* _nameText;
	TextComponent* _valueText;
	SpriteComponent* _barSprite;
	SpriteComponent* _knobSprite;
	std::string _name;

};