#pragma once
#include "ECS.hpp"
#include "Vector2.hpp"

class TransformComponent : public Component
{
public:
	TransformComponent();
	TransformComponent(Vector2 pos, double angle, Vector2 scale);
	Vector2 pos;
	double angle;
	Vector2 scale;
};