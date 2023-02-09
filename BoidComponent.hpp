#pragma once
#include <map>
#include "TransformComponent.hpp"
#include "Utils.hpp"
#include "RenderWindow.hpp"
#include "SteerRandom.hpp"
#include "BoundaryComponent.hpp"

class SteeringBehaviour;

struct Boundary
{
	Boundary(float radius, TransformComponent* transform);
	float radius;
	TransformComponent* transform;
};

class BoidComponent : public Component
{
public:
	BoidComponent();
	BoidComponent(float maxSpeed, float maxAcc, float width, float height, float maxAngle, float viewRadius, std::vector<BoidComponent*>* flock);
	~BoidComponent();
	void update() override;
	void init() override;
	Vector2 avoidObstacles();
	virtual void deleteBoid();
	virtual Vector2 steer();
	bool isBehind(Vector2 lookDir);
	TransformComponent* transform;
	static std::vector<BoidComponent*> allBoids;
	static float maxTurnAngle;
	std::vector<BoidComponent*>* flock;
	std::map<std::string, SteeringBehaviour*> behavoiursMap;
	float maxAngle;
	float maxSpeed;
	float maxAcc;
	Vector2 velocity;
	Vector2 acceleration;
	float width;
	float height;
	float viewRadius;
protected:
	Vector2 zeroDir = Vector2(0, -1);
	float _obstacleAvoidWeight;
	float _obstacleAvoidRadius;
	float minVelocity = .2f;
	Vector2 _heading;
};