#include "Seperation.hpp"

Seperation::Seperation(float weight, float avoidRadius) : SteeringBehaviour(weight)
{
	_useRadius = true;
	this->avoidRadius = avoidRadius;
}

Seperation::Seperation(float weight) : SteeringBehaviour(weight)
{
	avoidRadius = 100;
	_useRadius = false;
}



Vector2 Seperation::steer(std::vector<BoidComponent*>* boids, BoidComponent* self) 
{
	Vector2 steerDir(0, 0);
	for (auto boid : *boids)
	{
		if (boid == self) continue;
		float dist = boid->transform->pos.distance(self->transform->pos);
		Vector2 lookDir = boid->transform->pos - self->transform->pos;
		float maxAvoid = _useRadius ? avoidRadius : self->viewRadius;
		if (dist > maxAvoid || dist < .0001f) continue;
		Vector2 avoidDir = lookDir * -1 / powf(dist, 1.75);
		steerDir += avoidDir;
	}
	return steerDir.normalized() * weight;
}