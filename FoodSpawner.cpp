#include "FoodSpawner.hpp"

FoodSpawner::FoodSpawner()
{
	this->_minSpawnTime = 2;
	this->_maxSpawnTime = 4;
	this->_currSpawnTime =  utils::randomFloat(_minSpawnTime, _maxSpawnTime);
	this->_startingFood = 12;
}

void FoodSpawner::init()
{
	for (int i = 0; i < _startingFood; i++)
	{
		spawnFood();
	}
}

void FoodSpawner::update()
{
	_currSpawnTime -= Time::Instance().DeltaTime();
	if (_currSpawnTime <= 0)
	{
		_currSpawnTime = utils::randomFloat(_minSpawnTime, _maxSpawnTime);
		spawnFood();
	}
}

void FoodSpawner::spawnFood()
{
	Entity& food = EntityManager::Instance().addEntity();
	food.addComponent<TransformComponent>(Vector2(utils::randomFloat(-RenderWindow::Instance().WIDTH / 2, RenderWindow::Instance().WIDTH / 2),
		utils::randomFloat(-RenderWindow::Instance().HEIGHT / 2, RenderWindow::Instance().HEIGHT / 2)), 0, Vector2(1, 1));
	food.addComponent<WorldSpriteComponent>(Assets::Instance().foodSprite);
	foodComponents.push_back(& food.addComponent<FoodComponent>(this));
}