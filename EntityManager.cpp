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
	entities.erase(remove_if(begin(entities), end(entities),
		[](const unique_ptr<Entity>& mEntity)
		{
			return mEntity->isDestroyed();
		}),
		end(entities));
}

bool compareEntities(const std::unique_ptr<Entity>& e1, const std::unique_ptr<Entity>& e2)
{
	return e1->sortOrder < e2->sortOrder;
}

Entity& EntityManager::addEntity(int sortOrder)
{
	Entity* e = new Entity(sortOrder);
	std::unique_ptr<Entity> uPtr{ e };
	entities.emplace_back(std::move(uPtr));
	std::stable_sort(entities.begin(), entities.end(), compareEntities);
	return *e;
}

void EntityManager::clearEntities()
{
	entities.clear();
}

