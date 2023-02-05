#pragma once
#include "SteeringBehaviour.hpp"

class Cohesion : public SteeringBehaviour
{
public:
	Cohesion(float weight);
	Vector2 steer(std::vector<BoidComponent*>* boids, BoidComponent* self) override;
};