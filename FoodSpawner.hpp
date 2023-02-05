#pragma once
#include "Time.hpp"
#include "ECS.hpp"
#include "FoodComponent.hpp"
#include "EntityManager.hpp"
#include "Utils.hpp"
#include "BoundaryComponent.hpp"

class FoodComponent;

class FoodSpawner : public Component
{
public:
	FoodSpawner(Vector2 minPos, Vector2 maxPos);
	void update() override;
	void init() override;
	std::vector<FoodComponent*> foodComponents;
	float spawnRate = 0;
	float maxSpawnRate = 0;
	float currSpawnTime = 0;

private:
	int _startingFood = 0;
	void spawnFood();
	Vector2 _minPos;
	Vector2 _maxPos;
	const float c_foodRadius = 8;
};