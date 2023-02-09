#include "FoodSpawner.hpp"

FoodSpawner::FoodSpawner(Vector2 minPos, Vector2 maxPos)
{
	this->maxSpawnRate = 4;
	this->spawnRate = .3f * maxSpawnRate;
	this->currSpawnTime =  1 / spawnRate;
	this->_startingFood = 12;
	this->_minPos = minPos;
	this->_maxPos = maxPos;
}

void FoodSpawner::init()
{
	for (int i = 0; i < _startingFood; i++)
	{
		spawnFood();
	}
}

void FoodSpawner::update()
{
	currSpawnTime -= Time::Instance().DeltaTime();
	if (currSpawnTime <= 0)
	{
		currSpawnTime = 1 / spawnRate;
		spawnFood();
	}
}

void FoodSpawner::spawnFood()
{
	int tries = 0;
	Vector2 spawnPos(0, 0);
	while (tries < 1000)
	{
		bool validSpawn = true;
		spawnPos = Vector2(utils::randomFloat(_minPos.x, _maxPos.x), utils::randomFloat(_minPos.y, _maxPos.y));
		for (auto boundary : BoundaryComponent::boundaries)
		{
			if (spawnPos.distance(boundary->transform->pos) < boundary->radius + c_foodRadius)
			{
				validSpawn = false;
				break;
			}
		}
		if (validSpawn)
			break;
		tries++;
	}
	if (tries == 1000) return;
	Entity& food = EntityManager::Instance().addEntity(0);
	food.addComponent<TransformComponent>(spawnPos, 0, Vector2(1, 1));
	food.addComponent<WorldSpriteComponent>(Assets::Instance().foodSprite);
	foodComponents.push_back(& food.addComponent<FoodComponent>(this));
}