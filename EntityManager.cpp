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
		if (entities[i]->isActive())
			entities[i]->update();
	}
}

void EntityManager::render()
{
	for (size_t i = 0; i < entities.size(); i++)
	{
		if (entities[i]->isActive())
			entities[i]->render();
	}
}

void EntityManager::refresh()
{
	using namespace std;
	if (entities.empty()) return;
	for (size_t i = 0; i < entities.size(); i++)
	{
		if (entities[i]->isDestroyed())
		{
			delete entities[i];
			entities.erase(entities.begin() + i);
			i--;
		}
	}
	/*
	entities.erase(remove_if(begin(entities), end(entities),
		[](const unique_ptr<Entity>& mEntity)
		{
			return mEntity->isDestroyed();
		}),
		end(entities));
	*/
}

bool compareEntities(Entity* e1, Entity* e2)
{
	return e1->sortOrder < e2->sortOrder;
}

Entity& EntityManager::addEntity(int sortOrder)
{
	Entity* e = new Entity(sortOrder);
	entities.emplace_back(e);
	std::stable_sort(entities.begin(), entities.end(), compareEntities);
	return *e;
}

void EntityManager::clearEntities()
{
	for (size_t i = 0; i < entities.size(); i++)
		delete entities[i];
	entities.clear();
}

