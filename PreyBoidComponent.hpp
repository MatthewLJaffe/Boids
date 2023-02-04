#pragma once
#include "PredatorBoid.hpp"
#include "Seperation.hpp"
#include "Alignment.hpp"
#include "Cohesion.hpp"
#include "FoodSpawner.hpp"

class PredatorBoid;
class FoodSpawner;

class PreyBoidComponent : public BoidComponent
{
public:
	static std::vector<BoidComponent*> preyBoids;
	PreyBoidComponent(float maxSpeed, float maxAcc, float width, float height, float maxAngle, std::vector<BoidComponent*>* flock, FoodSpawner* foodSpawner);
	void init() override;
	void update() override;
	void deleteBoid() override;
	Vector2 steer() override;
	Vector2 steerTowardsFood();
	static float foodWeight;
	static int foodToReproduce;
private:
	float _currFoodObtained = 0;
	float _foodRadius = 0;
	FoodSpawner* _foodSpawner;
	void checkForFood();
	void spawnBoid();
};