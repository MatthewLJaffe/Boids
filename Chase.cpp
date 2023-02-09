#include "Chase.hpp"

Chase::Chase(float weight, float chaseTime) : SteeringBehaviour(weight)
{
	this->_chaseTime = chaseTime;
	this->_currChaseTime = 0;
	this->_currTarget = nullptr;
}

Vector2 Chase::steer(std::vector<BoidComponent*>* boids, BoidComponent* self)
{
	if (_currChaseTime > 0)
	{
		_currChaseTime -= Time::Instance().DeltaTime();
		if (_currTarget == nullptr)
		{
			return Vector2(0, 0);
		}
		else
		{
			return (_currTarget->pos - self->transform->pos).normalized() * weight;
		}
	}
	_currTarget = nullptr;
	float closestDist = self->viewRadius;
	BoidComponent* closestBoid = nullptr;
	for (auto& boid : *boids)
	{
		if (self->isBehind(boid->transform->pos - self->transform->pos)) continue;
		float dist = self->transform->pos.distance(boid->transform->pos);
		if (dist <= closestDist)
		{
			closestDist = dist;
			closestBoid = boid;
		}
	}
	if (closestBoid == nullptr)
		return Vector2(0, 0);
	_currTarget = closestBoid->transform;
	_currChaseTime = _chaseTime;
	return (closestBoid->transform->pos - self->transform->pos).normalized() * weight;
}

void Chase::delayChase(float time)
{
	_currChaseTime = time;
	_currTarget = nullptr;
}


