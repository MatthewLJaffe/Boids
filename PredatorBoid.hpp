#pragma once
#include "BoidComponent.hpp"
#include "Chase.hpp"
#include "Seperation.hpp"
#include "PreyBoidComponent.hpp"
#include "Utils.hpp"
#include "WorldSpriteComponent.hpp"

class PredatorBoid : public BoidComponent
{
public:
	PredatorBoid(float maxSpeed, float maxAcc, float width, float height, float maxAngle, float viewRadius, std::vector<BoidComponent*>* flock);
	static std::vector<BoidComponent*> predatorBoids;
	static int foodToRespawn;
	static float liveTimeWithoutFood;
	void deleteBoid() override;
	void init() override;
	void update() override;
	Vector2 steer() override;
private:
	float _currTime = 0;
	int _preyEaten = 0;
	float _eatTime;
	float _currEatTime;
	void spawnBoid();
};