#include "EntityManager.hpp"

EntityManager& EntityManager::Instance()
{
	static EntityManager entityManagerInstance;
	return entityManagerInstance;
}

EntityManager::EntityManager() {}

void EntityManager::update()
{
	for (size_t i = 0; i < entities.size(); i++)
	{
		entities[i]->update();
	}
}

void EntityManager::render()
{
	for (size_t i = 0; i < entities.size(); i++)
	{
		entities[i]->render();
	}
}

void EntityManager::refresh()
{
	using namespace std;
	if (entities.empty()) return;
	entities.erase(remove_if(begin(entities), end(entities),
		[](const unique_ptr<Entity>& mEntity)
		{
			return !mEntity->isActive();
		}),
		end(entities));
}

Entity& EntityManager::addEntity()
{
	Entity* e = new Entity();
	std::unique_ptr<Entity> uPtr{ e };
	entities.emplace_back(std::move(uPtr));
	return *e;
}