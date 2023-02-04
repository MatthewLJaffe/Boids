#include "PredatorBoid.hpp"

std::vector<BoidComponent*> PredatorBoid::predatorBoids;

PredatorBoid::PredatorBoid(float maxSpeed, float maxAcc, float width, float height, float maxAngle, std::vector<BoidComponent*>* flock)
	: BoidComponent(maxSpeed, maxAcc, width, height, maxAngle, flock)
{
	behavoiursMap["SteerRandom"] = new SteerRandom(.1);
	behavoiursMap["Chase"] = new Chase(.7, 200, 2, maxAngle);
	behavoiursMap["Seperation"] = new Seperation(.2, 200);
	_currEatTime = 0;
	_eatTime = 2.5;
}

void PredatorBoid::init()
{
	predatorBoids.push_back(this);
	BoidComponent::init();
}

void PredatorBoid::update()
{
	if (_currEatTime > 0)
	{
		_currEatTime -= Time::Instance().DeltaTime();
		return;
	}

	for (size_t i = 0; i < PreyBoidComponent::preyBoids.size(); i++)
	{
		if (utils::boxCollision(transform->pos.x, transform->pos.y, width, height,
			PreyBoidComponent::preyBoids[i]->transform->pos.x, PreyBoidComponent::preyBoids[i]->transform->pos.y, 
			PreyBoidComponent::preyBoids[i]->width, PreyBoidComponent::preyBoids[i]->height))
		{
			PreyBoidComponent::preyBoids[i]->deleteBoid();
			transform->scale += Vector2(.1, .1);
			_currEatTime = _eatTime;
		}
	}
	BoidComponent::update();
}

Vector2 PredatorBoid::steer()
{
	Vector2 steerDir(0, 0);
	for (auto& pair : behavoiursMap)
	{
		if (pair.first == "Seperation")
		{
			steerDir += pair.second->steer(&PredatorBoid::predatorBoids, this);
		}
		else
		{
			steerDir += pair.second->steer(&PreyBoidComponent::preyBoids, this);
		}
	}
	steerDir += avoidObstacles();
	return steerDir;
}

