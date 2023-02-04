#pragma once
#include "SteeringBehaviour.hpp"

class Cohesion : public SteeringBehaviour
{
public:
	Cohesion(float weight, float alignRadius);
	Vector2 steer(std::vector<BoidComponent*>* boids, BoidComponent* self) override;
private:
	float _coheisonRadius;
};