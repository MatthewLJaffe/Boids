#include "Cohesion.hpp"

Cohesion::Cohesion(float weight, float cohesionRadius)
{
	this->weight = weight;
	this->_coheisonRadius = cohesionRadius;
}

Vector2 Cohesion::steer(std::vector<BoidComponent*>* boids, BoidComponent* self)
{
	Vector2 avgPos(0, 0);
	float nearby = 0;
	for (auto boid : *boids)
	{
		if (boid == self || self->transform->pos.distance(boid->transform->pos) > _coheisonRadius) continue;
		avgPos += boid->transform->pos;
		nearby++;
	}
	if (nearby == 0) return avgPos;
	avgPos /= nearby;
	Vector2 steerDir = avgPos - self->transform->pos;
	return steerDir.normalized() * weight;
}