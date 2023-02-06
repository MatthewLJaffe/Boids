#pragma once
#include "ECS.hpp"

class EntityManager
{
public:
	EntityManager(const EntityManager&) = delete;
	static EntityManager& Instance();
	std::vector<Entity*> entities;
	void update();
	void render();
	void refresh();
	void clearEntities();
	Entity& addEntity(int sortOrder);
private:
	EntityManager();
};