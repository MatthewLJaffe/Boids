#include "FoodSlider.hpp"

FoodSlider::FoodSlider(std::string name, float minValaue, float maxValue, float startValue, float minX, float maxX, TextComponent* nameText, TextComponent* amountText, SpriteComponent* knobSprite, std::string sliderParameter, bool round)
	: SliderComponent(name, minValaue, maxValue, startValue, minX, maxX, nameText, amountText, knobSprite, round)
{
	this->_sliderParameter = sliderParameter;
}

void FoodSlider::setFoodSpawner(FoodSpawner* foodSpawner)
{
	this->_foodSpawner = foodSpawner;
}

void FoodSlider::onValueUpdate()
{
	if (_foodSpawner == nullptr) return;
	if (_sliderParameter == "Spawn Rate")
	{
		_foodSpawner->spawnRate = _foodSpawner->maxSpawnRate * _value;
	}
	if (_sliderParameter == "Food to Reproduce")
	{
		PreyBoidComponent::foodToReproduce = utils::roundFloat(_value);
	}
}