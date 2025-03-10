#include "Alignment.hpp"

Alignment::Alignment(float weight) : SteeringBehaviour(weight)
{}

Vector2 Alignment::steer(std::vector<BoidComponent*>* boids, BoidComponent* self)
{
	Vector2 steerPos(0, 0);
	for (auto boid : *boids)
	{
		if (boid == self || self->transform->pos.distance(boid->transform->pos) > self->viewRadius) continue;
		if (self->isBehind(boid->transform->pos - self->transform->pos)) continue;
		steerPos += boid->velocity.normalized();
	}
	return steerPos.normalized() * weight;
}
