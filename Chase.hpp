#pragma once
#include "SteeringBehaviour.hpp"
#include "Time.hpp"
#include "TransformComponent.hpp"

class Chase : public SteeringBehaviour
{
public:
	Chase(float weight, float chaseTime);
	Vector2 steer(std::vector<BoidComponent*>* boids, BoidComponent* self) override;
	void delayChase(float time);
private:
	float _chaseTime;
	float _currChaseTime;
	TransformComponent* _currTarget;
	bool isBehind(Vector2 heading, Vector2 lookDir, float maxAngle);
};