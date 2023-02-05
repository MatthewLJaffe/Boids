#include "PredatorSlider.hpp"

PredatorSlider::PredatorSlider(std::string name, float minValaue, float maxValue, float startValue, float minX, float maxX, TextComponent* nameText, TextComponent* amountText, SpriteComponent* knobSprite, std::string sliderParameter)
	: SliderComponent(name, minValaue, maxValue, startValue, minX, maxX, nameText, amountText, knobSprite)
{
	this->_sliderParameter = sliderParameter;
}

PredatorSlider::PredatorSlider(std::string name, float minValaue, float maxValue, float startValue, float minX, float maxX, TextComponent* nameText, TextComponent* amountText, SpriteComponent* knobSprite, std::string sliderParameter, bool round)
	: SliderComponent(name, minValaue, maxValue, startValue, minX, maxX, nameText, amountText, knobSprite, round)
{
	this->_sliderParameter = sliderParameter;
}

void PredatorSlider::onValueUpdate()
{
	if (_sliderParameter == "Speed")
	{
		for (size_t i = 0; i < PredatorBoid::predatorBoids.size(); i < i++)
		{
			PredatorBoid::predatorBoids[i]->maxSpeed = _value;
		}
	}
	else if (_sliderParameter == "Acceleration")
	{
		for (size_t i = 0; i < PredatorBoid::predatorBoids.size(); i < i++)
		{
			PredatorBoid::predatorBoids[i]->maxAcc = _value / 100;
		}
	}
	else if (_sliderParameter == "Field of View")
	{
		for (size_t i = 0; i < PredatorBoid::predatorBoids.size(); i < i++)
		{
			PredatorBoid::predatorBoids[i]->maxAngle = _value / 2;
		}
	}
	else if (_sliderParameter == "Vision Radius")
	{
		for (size_t i = 0; i < PredatorBoid::predatorBoids.size(); i < i++)
		{
			PredatorBoid::predatorBoids[i]->viewRadius = _value;
		}
	}
	else if (_sliderParameter == "Aggression")
	{
		for (size_t i = 0; i < PredatorBoid::predatorBoids.size(); i < i++)
		{
			PredatorBoid::predatorBoids[i]->behavoiursMap["Chase"]->weight = _value;
		}
	}
	else if (_sliderParameter == "Food to Reproduce")
	{
		PredatorBoid::foodToRespawn = _value;
	}
	else if (_sliderParameter == "Starvation Time")
	{
		PredatorBoid::liveTimeWithoutFood = _value;
	}
}