#include "Alignment.hpp"

Alignment::Alignment(float weight, float alignRadius)
{
	this->weight = weight;
	this->_alignRadius = alignRadius;
}

Vector2 Alignment::steer(std::vector<BoidComponent*>* boids, BoidComponent* self)
{
	Vector2 steerPos(0, 0);
	for (auto boid : *boids)
	{
		if (boid == self || self->transform->pos.distance(boid->transform->pos) > _alignRadius) continue;
		steerPos += boid->velocity.normalized();
	}
	return steerPos.normalized() * weight;
}
