#include "PredatorBoid.hpp"

std::vector<BoidComponent*> PredatorBoid::predatorBoids;
int PredatorBoid::foodToRespawn = 5;
float PredatorBoid::liveTimeWithoutFood = 25;

PredatorBoid::PredatorBoid(float maxSpeed, float maxAcc, float width, float height, float maxAngle, float viewRadius, std::vector<BoidComponent*>* flock)
	: BoidComponent(maxSpeed, maxAcc, width, height, maxAngle, viewRadius, flock)
{
	behavoiursMap["SteerRandom"] = new SteerRandom(.1);
	behavoiursMap["Chase"] = new Chase(.7, 2.5);
	behavoiursMap["Seperation"] = new Seperation(.2);
	_currEatTime = 0;
	_eatTime = 2;
	_currTime = 0;
}

void PredatorBoid::init()
{
	predatorBoids.push_back(this);
	BoidComponent::init();
}

void PredatorBoid::update()
{
	_currTime += Time::Instance().DeltaTime();
	if (_currTime >= liveTimeWithoutFood)
	{
		deleteBoid();
		return;
	}
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
			_currEatTime = _eatTime;
			_currTime = 0;
			_preyEaten++;
			if (_preyEaten >= foodToRespawn)
			{
				spawnBoid();
				_preyEaten = 0;
			}
		}
	}
	BoidComponent::update();
}

void PredatorBoid::deleteBoid()
{
	for (size_t i = 0; i < predatorBoids.size(); i++)
	{
		if (predatorBoids[i] == this)
		{
			predatorBoids.erase(predatorBoids.begin() + i);
			break;
		}
	}
	BoidComponent::deleteBoid();
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

void PredatorBoid::spawnBoid()
{
	Entity& predatorEntity = EntityManager::Instance().addEntity(1);
	predatorEntity.addComponent<TransformComponent>(transform->pos, 0, Vector2(1, 1));
	predatorEntity.addComponent<WorldSpriteComponent>(entity->getComponent<WorldSpriteComponent>().sprite);
	predatorEntity.addComponent<PredatorBoid>(maxSpeed, maxAcc, width, height, maxAngle, viewRadius, flock);
	
}

