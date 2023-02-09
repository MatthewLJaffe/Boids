#pragma once
#include "Vector2.hpp"
#include <vector>


class BoidComponent;

class SteeringBehaviour
{
public:
	SteeringBehaviour(float weight);
	virtual ~SteeringBehaviour();
	float weight = 0;
	virtual Vector2 steer(std::vector<BoidComponent*>* boids, BoidComponent* self) = 0;
};

#include "BoidComponent.hpp"