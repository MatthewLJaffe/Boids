#include "SteerRandom.hpp"

SteerRandom::SteerRandom(float weight)
{
	this->weight = weight;
	updateTime = utils::randomFloat(minUpdateTime, maxUpdateTime);
	_randomDir = Vector2(utils::randomFloat(-1, 1), utils::randomFloat(-1, 1));
}

Vector2 SteerRandom::steer(vector<BoidComponent*>* boids, BoidComponent* self)
{
	currTime += Time::Instance().DeltaTime();
	if (currTime >= updateTime)
	{
		updateTime = utils::randomFloat(minUpdateTime, maxUpdateTime);
		currTime = 0;
		_randomDir = self->velocity.normalized().rotate(static_cast<double>(utils::randomFloat(-120, 120)));
	}
	return _randomDir * weight;
}