#include "TransformComponent.hpp"

TransformComponent::TransformComponent()
{
	this->pos = Vector2(0, 0);
	this->angle = 0;
	this->scale = Vector2(1, 1);
}

TransformComponent::TransformComponent(Vector2 pos, double angle, Vector2 scale)
{
	this->pos = pos;
	this->angle = angle;
	this->scale = scale;
}