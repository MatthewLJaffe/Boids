#include "PreyBoidSlider.hpp"

PreyBoidSlider::PreyBoidSlider(std::string name, float minValue, float maxValue, float startValue, float minX, float maxX, TextComponent* nameText, TextComponent* amountText, SpriteComponent* knobSprite, std::string sliderParameter)
	: SliderComponent(name, minValue, maxValue, startValue, minX, maxX, nameText, amountText, knobSprite)
{
	this->_sliderParameter = sliderParameter;
}


void PreyBoidSlider::onValueUpdate()
{
	if (_sliderParameter == "Speed")
	{
		for (size_t i = 0; i < PreyBoidComponent::preyBoids.size(); i++)
		{
			PreyBoidComponent::preyBoids[i]->maxSpeed = _value;
		}
	}
	else if (_sliderParameter == "Acceleration")
	{
		for (size_t i = 0; i < PreyBoidComponent::preyBoids.size(); i++)
		{
			PreyBoidComponent::preyBoids[i]->maxAcc = _value/100;
		}
	}
	else if (_sliderParameter == "Food Attraction")
	{
		PreyBoidComponent::foodWeight = _value;
	}
	else if (_sliderParameter == "Field of View")
	{
		for (size_t i = 0; i < PreyBoidComponent::preyBoids.size(); i++)
		{
			PreyBoidComponent::preyBoids[i]->maxAngle = _value/2;
		}
	}
	else if (_sliderParameter == "Vision Radius")
	{
		for (size_t i = 0; i < PreyBoidComponent::preyBoids.size(); i++)
		{
			PreyBoidComponent::preyBoids[i]->viewRadius = _value;
		}
	}
	else
	{
		for (size_t i = 0; i < PreyBoidComponent::preyBoids.size(); i++)
		{
			if (PreyBoidComponent::preyBoids[i]->behavoiursMap.count(_sliderParameter) > 0)
				PreyBoidComponent::preyBoids[i]->behavoiursMap[_sliderParameter]->weight = _value;
		}
	}

}
