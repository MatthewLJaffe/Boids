#include "ECS.hpp"
int Entity::componentsAdded = 0;
void Component::init() {}
void Component::update() {}
void Component::render() {}

Component::~Component() 
{ 
	static int destroyed = 0;
	destroyed++;
	std::cout << "Destroy Component " << destroyed << std::endl; 
}
Entity::~Entity() 
{
	static int destroyed = 0;
	destroyed++;
	std::cout << "Destroy Entity " << destroyed << std::endl; 
}


Entity::Entity(int sortOrder)
{
	this->sortOrder = sortOrder;
}

void Entity::update()
{
	for (auto& c : components) 
		c->update();
}

void Entity::render()
{
	for (auto& c : components) 
		c->render();
}

void Entity::destroy()
{
	destroyed = true;
	for (size_t i = 0; i < children.size(); i++)
	{
		children[i]->destroy();
	}
}


bool Entity::isDestroyed()
{
	return destroyed;
}

void Entity::addChild(Entity* e)
{
	e->parent = this;
	children.push_back(e);
}

bool Entity::isActive()
{
	return active;
}

void Entity::setActive(bool isActive)
{
	active = isActive;
	for (auto child : children)
	{
		child->setActive(active);
	}
}