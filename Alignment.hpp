#pragma once
#include "SteeringBehaviour.hpp"

class Alignment : public SteeringBehaviour
{
public:
	Alignment(float weight);
	Vector2 steer(std::vector<BoidComponent*>* boids, BoidComponent* self) override;
};