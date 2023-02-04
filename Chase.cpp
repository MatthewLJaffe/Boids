#include "Chase.hpp"

Chase::Chase(float weight, float chaseRadius, float chaseTime, float maxAngle)
{
	this->weight = weight;
	this->_chaseRadius = chaseRadius;
	this->_chaseTime = chaseTime;
	this->_currChaseTime = 0;
	this->_currTarget = nullptr;
	this->_maxAngle = _maxAngle;
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
	float closestDist = _chaseRadius;
	BoidComponent* closestBoid = nullptr;
	for (auto& boid : *boids)
	{
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

bool Chase::isBehind(Vector2 heading, Vector2 lookDir)
{
	float angle = heading.angleBetween(lookDir);
	return angle >= _maxAngle && angle <= 360 - _maxAngle;
}

void Chase::delayChase(float time)
{
	_currChaseTime = time;
	_currTarget = nullptr;
}


