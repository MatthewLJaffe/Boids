#include "BoidComponent.hpp"
std::vector<BoidComponent*> BoidComponent::allBoids;
float BoidComponent::maxTurnAngle = 120;

Boundary::Boundary(float radius, TransformComponent* transform)
{
	this->radius = radius;
	this->transform = transform;
}

BoidComponent::BoidComponent() {}

BoidComponent::BoidComponent(float maxSpeed, float maxAcc, float width, float height, float maxAngle, float viewRadius, std::vector<BoidComponent*>* flock)
{
	this->maxSpeed = maxSpeed;
	this->velocity = Vector2(utils::randomFloat(-1,1), utils::randomFloat(-1, 1));
	velocity.normalize();
	velocity *= maxSpeed;
	this->acceleration = Vector2(0, 0);
	this->maxAcc = maxAcc;
	this->width = width;
	this->height = height;
	this->maxAngle = maxAngle;
	this->flock = flock;
	this->viewRadius = viewRadius;
	_obstacleAvoidRadius = 75;
	_obstacleAvoidWeight = 2;
}

void BoidComponent::init()
{
	flock->push_back(this);
	allBoids.push_back(this);
	transform = &entity->getComponent<TransformComponent>();
}

Vector2 BoidComponent::avoidObstacles()
{
	Vector2 steerDir(0, 0);
	for (size_t i = 0; i < BoundaryComponent::boundaries.size(); i++)
	{
		float dist = transform->pos.distance(BoundaryComponent::boundaries[i]->transform->pos);
		if (dist <= BoundaryComponent::boundaries[i]->radius + _obstacleAvoidRadius)
		{
			steerDir += (transform->pos - BoundaryComponent::boundaries[i]->transform->pos) / dist;
		}
	}
	return steerDir.normalized() * _obstacleAvoidWeight;
}

void BoidComponent::update()
{
	Vector2 steerDir = steer();
	float angle = velocity.angleBetween(steerDir);
	
	if (angle > maxTurnAngle && angle < 360 - maxTurnAngle)
	{
		if (angle > 180)
			steerDir = velocity.rotate(360 - maxTurnAngle);
		else
			steerDir = velocity.rotate(maxTurnAngle);
	}	
	acceleration = steerDir.normalized() * maxAcc;
	if (acceleration.mag() > maxAcc + .0001)
	{
		std::cout << "?" << std::endl;
	}
	velocity += acceleration;
	if (velocity.mag() > maxSpeed)
		velocity = velocity.normalized() * maxSpeed;
	transform->pos += velocity;
	transform->angle = zeroDir.angleBetween(velocity);
	if (transform->angle > 360 || transform->angle < 0)
		transform->angle += 360;
}

Vector2 BoidComponent::steer()
{
	Vector2 steerDir(0, 0);
	for (auto& pair : behavoiursMap)
	{
		steerDir += pair.second->steer(flock, this);
	}
	steerDir += avoidObstacles();
	return steerDir;
}

void BoidComponent::deleteBoid()
{
	for (size_t i = 0; i < flock->size(); i++)
	{
		if ((*flock)[i] == this)
		{
			flock->erase(flock->begin() + i);
			break;
		}
	}

	for (size_t i = 0; i < BoidComponent::allBoids.size(); i++)
	{
		if (BoidComponent::allBoids[i] == this)
		{
			BoidComponent::allBoids.erase(BoidComponent::allBoids.begin() + i);
			break;
		}
	}

	entity->destroy();
}

bool BoidComponent::isBehind(Vector2 lookDir)
{
	float angle = velocity.angleBetween(lookDir);
	return angle >= maxAngle && angle <= 360 - maxAngle;
}


BoidComponent::~BoidComponent()
{
	for (auto& pair : behavoiursMap)
	{
		delete pair.second;
	}
}
