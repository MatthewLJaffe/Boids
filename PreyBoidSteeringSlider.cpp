#include "PreyBoidSteeringSlider.hpp"

PreyBoidSteeringSlider::PreyBoidSteeringSlider(std::string name, float minValue, float maxValue, float startValue, float minX, float maxX, std::string steeringBehaviour)
	: SliderComponent(name, minValue, maxValue, startValue, minX, maxX)
{
	this->_steeringBehaviour = steeringBehaviour;
}


void PreyBoidSteeringSlider::onValueUpdate()
{
	for (size_t i = 0; i < PreyBoidComponent::preyBoids.size(); i++)
	{
		PreyBoidComponent::preyBoids[i]->behavoiursMap[_steeringBehaviour]->weight = _value;
	}
}
