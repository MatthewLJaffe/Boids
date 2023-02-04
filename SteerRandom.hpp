#pragma once
#include "SteeringBehaviour.hpp"
#include "Time.hpp"
#include "Utils.hpp"

class BoidComponent;

class SteerRandom : public SteeringBehaviour
{
public:
	SteerRandom(float weight);
	Vector2 steer(std::vector<BoidComponent*>* boids, BoidComponent* self) override;
	const float minUpdateTime = .5f;
	const float maxUpdateTime = 2;
	float updateTime = 0;
	float currTime = 0;
private:
	Vector2 _randomDir;

};