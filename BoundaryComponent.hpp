#pragma once
#include "ECS.hpp"
#include "TransformComponent.hpp"
#include "BoidComponent.hpp"

class BoundaryComponent : public Component
{
public:
	BoundaryComponent(float radius);
	void init() override;
	void update() override;
	static std::vector<BoundaryComponent*> boundaries;
	TransformComponent* transform;
	float radius;
};