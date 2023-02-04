#pragma once
#include "Time.hpp"
#include "ECS.hpp"
#include "FoodComponent.hpp"
#include "EntityManager.hpp"
#include "Utils.hpp"

class FoodComponent;

class FoodSpawner : public Component
{
public:
	FoodSpawner();
	void update() override;
	void init() override;
	std::vector<FoodComponent*> foodComponents;

private:
	float _minSpawnTime = 0;
	float _maxSpawnTime = 0;
	float _currSpawnTime = 0;
	int _startingFood = 0;
	void spawnFood();
};