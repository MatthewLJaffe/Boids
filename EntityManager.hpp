#pragma once
#include "ECS.hpp"

class EntityManager
{
public:
	EntityManager(const EntityManager&) = delete;
	static EntityManager& Instance();
	std::vector<std::unique_ptr<Entity>> entities;
	void update();
	void render();
	void refresh();
	Entity& addEntity();
private:
	EntityManager();
};