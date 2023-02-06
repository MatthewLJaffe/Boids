#include "PreyBoidComponent.hpp"
std::vector<BoidComponent*> PreyBoidComponent::preyBoids;
float PreyBoidComponent::foodWeight = .5;
int PreyBoidComponent::foodToReproduce = 2;

PreyBoidComponent::PreyBoidComponent(float maxSpeed, float maxAcc, float width, float height, float maxAngle, float viewRadius, std::vector<BoidComponent*>* flock, FoodSpawner* foodSpawner)
	: BoidComponent(maxSpeed, maxAcc, width, height, maxAngle, viewRadius, flock)
{
	behavoiursMap["SteerRandom"] = new SteerRandom(.05);
	behavoiursMap["Seperation"] = new Seperation(.35, 75);
	behavoiursMap["Alignment"] = new Alignment(.3);
	behavoiursMap["Cohesion"] = new Cohesion(.3);
	behavoiursMap["AvoidPredators"] = new Seperation(.75);
	this->_foodSpawner = foodSpawner;
	this->_foodRadius = 250;
}

void PreyBoidComponent::init()
{
	preyBoids.push_back(this);
	BoidComponent::init();
}

void PreyBoidComponent::update()
{
	checkForFood();
	BoidComponent::update();
}

Vector2 PreyBoidComponent::steer()
{
	Vector2 steerDirection;
	for (auto& pair : behavoiursMap)
	{
		if (pair.first == "Seperation")
		{
			steerDirection += pair.second->steer(&PreyBoidComponent::preyBoids, this);
		}
		else if (pair.first == "AvoidPredators")
		{
			steerDirection += pair.second->steer(&PredatorBoid::predatorBoids, this);
		}
		else
		{
			steerDirection += pair.second->steer(flock, this);
		}
	}
	steerDirection += avoidObstacles();
	steerDirection += steerTowardsFood();
	return steerDirection;
}

void PreyBoidComponent::deleteBoid()
{
	for (size_t i = 0; i < PreyBoidComponent::preyBoids.size(); i++)
	{
		if (PreyBoidComponent::preyBoids[i] == this)
		{
			PreyBoidComponent::preyBoids.erase(PreyBoidComponent::preyBoids.begin() + i);
			break;
		}
	}
	BoidComponent::deleteBoid();
}

void PreyBoidComponent::checkForFood()
{
	for (size_t i = 0; i < _foodSpawner->foodComponents.size(); i++)
	{
		if (transform->pos.distance(_foodSpawner->foodComponents[i]->transform.pos) < _foodSpawner->foodComponents[i]->radius)
		{
			_foodSpawner->foodComponents[i]->consumeFood();
			_currFoodObtained++;
			if (_currFoodObtained >= foodToReproduce)
			{
				spawnBoid();
				_currFoodObtained = 0;
			}
			break;
		}
	}
}

void PreyBoidComponent::spawnBoid()
{
	Entity& preyEntity = EntityManager::Instance().addEntity(0);
	preyEntity.addComponent<TransformComponent>(transform->pos, 0, Vector2(1, 1));
	preyEntity.addComponent<WorldSpriteComponent>(entity->getComponent<WorldSpriteComponent>().sprite);
	preyEntity.addComponent<PreyBoidComponent>(maxSpeed, maxAcc, width, height, maxAngle,viewRadius, flock, _foodSpawner);
}

Vector2 PreyBoidComponent::steerTowardsFood()
{
	float closestDistance = _foodRadius;
	Vector2 closestDir = Vector2(0, 0);
	for (size_t i = 0; i < _foodSpawner->foodComponents.size(); i++)
	{
		if (isBehind(transform->pos - _foodSpawner->foodComponents[i]->transform.pos)) continue;
		float dist = transform->pos.distance(_foodSpawner->foodComponents[i]->transform.pos);
		if (dist < closestDistance)
		{
			closestDistance = dist;
			closestDir = _foodSpawner->foodComponents[i]->transform.pos - transform->pos;
		}
	}
	return closestDir.normalized() * foodWeight;
}