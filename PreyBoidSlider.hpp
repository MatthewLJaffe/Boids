#pragma once
#include "SliderComponent.hpp"
#include "PreyBoidComponent.hpp"

class PreyBoidSlider : public SliderComponent
{
public:
	PreyBoidSlider(std::string name, float minValaue, float maxValue, float startValue, float minX, float maxX, TextComponent* nameText, TextComponent* amountText, SpriteComponent* knobSprite, std::string sliderParameter);
protected:
	void onValueUpdate() override;
private:
	std::string _sliderParameter;
};