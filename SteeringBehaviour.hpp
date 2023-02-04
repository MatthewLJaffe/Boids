#pragma once
#include "Vector2.hpp"
#include <vector>


class BoidComponent;

class SteeringBehaviour
{
public:
	float weight;
	virtual Vector2 steer(std::vector<BoidComponent*>* boids, BoidComponent* self) = 0;
};

#include "BoidComponent.hpp"