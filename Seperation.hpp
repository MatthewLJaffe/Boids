#pragma once
#include "SteeringBehaviour.hpp"

class Seperation : public SteeringBehaviour
{
public:
	Seperation(float weight, float avoidRadius);
	Seperation(float weight);
	Vector2 steer(std::vector<BoidComponent*>* boids, BoidComponent* self) override;

private:
	float avoidRadius;
	bool _useRadius = false;
};