#pragma once
#include "SliderComponent.hpp"
#include "PreyBoidComponent.hpp"

class PreyBoidSteeringSlider : public SliderComponent
{
public:
	PreyBoidSteeringSlider(std::string name, float minValaue, float maxValue, float startValue, float minX, float maxX, std::string steeringBehaviour);
protected:
	void onValueUpdate() override;
private:
	std::string _steeringBehaviour;
};