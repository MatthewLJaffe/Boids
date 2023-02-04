#include "FoodComponent.hpp"

FoodComponent::FoodComponent(FoodSpawner* foodSpawner)
{
	this->radius = 16;
	this->_consumed = false;
	this->_foodSpawner = foodSpawner;
}

void FoodComponent::init()
{
	this->transform = entity->getComponent<TransformComponent>();
}

void FoodComponent::consumeFood()
{
	if (_consumed) return;
	for (size_t i = 0; i < _foodSpawner->foodComponents.size(); i++)
	{
		if (_foodSpawner->foodComponents[i] == this)
		{
			_foodSpawner->foodComponents.erase(_foodSpawner->foodComponents.begin() + i);
			break;
		}
	}
	_consumed = true;
	entity->destroy();
}


