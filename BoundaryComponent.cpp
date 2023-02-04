#include "BoundaryComponent.hpp"

std::vector<BoundaryComponent*> BoundaryComponent::boundaries;

BoundaryComponent::BoundaryComponent(float radius)
{
	this->radius = radius;
	boundaries.push_back(this);
}

void BoundaryComponent::init()
{
	this->transform = &entity->getComponent<TransformComponent>();
}

void BoundaryComponent::update()
{
	for (size_t i = 0; i < BoidComponent::allBoids.size(); i++)
	{
		if (transform->pos.distance(BoidComponent::allBoids[i]->transform->pos) < radius + BoidComponent::allBoids[i]->height / 2)
		{
			Vector2 moveDir = BoidComponent::allBoids[i]->transform->pos - transform->pos;
			moveDir = moveDir.normalized() * (BoidComponent::allBoids[i]->height / 2 + radius);
			BoidComponent::allBoids[i]->transform->pos = transform->pos + moveDir;
		}
	}
}