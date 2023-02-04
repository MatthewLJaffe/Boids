#pragma once
#include "ECS.hpp"
#include "SDL_image.h"
#include "SDL_TTF.h"
#include "SpriteComponent.hpp"
#include "InputManager.hpp"
#include "Assets.hpp"
#include "Utils.hpp"
#include <cmath>

class SliderComponent : public Component
{
public:
	SliderComponent(std::string name, float minValaue, float maxValue, float startValue, float minX, float maxX);
	void update() override;
	void render() override;
	void init() override;
protected:
	void updateValueText(std::string message);
	virtual void onValueUpdate();
	float _minValue;
	float _maxValue;
	float _minX;
	float _maxX;
	float _value;
	float _knobRadius;
	float _lastMouseX;
	bool _sliderMove = false;
	Vector2 _amountTextOffset;
	Vector2 _nameTextOffset;
	SpriteComponent* _knobSprite;
	SDL_Texture* nameText;
	SDL_Texture* amountText;
	SDL_Rect nameSrc;
	SDL_Rect nameDst;
	SDL_Rect amountSrc;
	SDL_Rect amountDst;
	std::string _name;

};