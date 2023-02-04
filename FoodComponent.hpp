#pragma once
#include "ECS.hpp"
#include "Time.hpp"
#include "Game.hpp"
#include "FoodSpawner.hpp"

class FoodSpawner;

class FoodComponent : public Component
{
public:
	FoodComponent(FoodSpawner* foodSpawner);
	void init() override;
	float radius = 0;
	TransformComponent transform;
	void consumeFood();

private:
	bool _consumed = false;
	FoodSpawner* _foodSpawner;
};