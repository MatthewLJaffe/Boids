#include "Cohesion.hpp"

Cohesion::Cohesion(float weight)
{
	this->weight = weight;
}

Vector2 Cohesion::steer(std::vector<BoidComponent*>* boids, BoidComponent* self)
{
	Vector2 avgPos(0, 0);
	float nearby = 0;
	for (auto boid : *boids)
	{
		if (boid == self || self->transform->pos.distance(boid->transform->pos) > self->viewRadius) continue;
		if (self->isBehind(boid->transform->pos - self->transform->pos)) continue;
		avgPos += boid->transform->pos;
		nearby++;
	}
	if (nearby == 0) return avgPos;
	avgPos /= nearby;
	Vector2 steerDir = avgPos - self->transform->pos;
	return steerDir.normalized() * weight;
}