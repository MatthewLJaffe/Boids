#pragma once
#include "SliderComponent.hpp"
#include "FoodSpawner.hpp"

class FoodSpawner;

class FoodSlider : public SliderComponent
{
public:
	FoodSlider(std::string name, float minValaue, float maxValue, float startValue, float minX, float maxX, TextComponent* nameText, TextComponent* amountText, SpriteComponent* knobSprite, std::string sliderParameter, bool round);
	void setFoodSpawner(FoodSpawner* foodSpawner);
protected:
	void onValueUpdate() override;
private:
	std::string _sliderParameter;
	FoodSpawner* _foodSpawner = nullptr;
};
