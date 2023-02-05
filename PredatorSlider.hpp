#pragma once
#include "PredatorBoid.hpp"
#include "SliderComponent.hpp"

class PredatorSlider : public SliderComponent
{
public:
	PredatorSlider(std::string name, float minValaue, float maxValue, float startValue, float minX, float maxX, TextComponent* nameText, TextComponent* amountText, SpriteComponent* knobSprite, std::string sliderParameter);
	PredatorSlider(std::string name, float minValaue, float maxValue, float startValue, float minX, float maxX, TextComponent* nameText, TextComponent* amountText, SpriteComponent* knobSprite, std::string sliderParameter, bool round);

protected:
	void onValueUpdate() override;
private:
	std::string _sliderParameter;
};