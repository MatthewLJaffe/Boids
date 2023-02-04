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
	PredatorBoid(float maxSpeed, float maxAcc, float width, float height, float maxAngle, std::vector<BoidComponent*>* flock);
	static std::vector<BoidComponent*> predatorBoids;
	void init() override;
	void update() override;
	Vector2 steer() override;
private:
	float _eatTime;
	float _currEatTime;
};