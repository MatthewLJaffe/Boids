#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
using ComponentID = std::size_t;

inline ComponentID getComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity* entity = nullptr;
	virtual void init();
	virtual void update();
	virtual void render();
	virtual ~Component();
};

class Entity
{
private:
	bool destroyed = false;
	bool active = true;
	std::vector<Component*> components;
	std::vector<Entity*> children;
	ComponentArray componentArray;
	ComponentBitSet componentBitSet;

public:
	virtual ~Entity();
	Entity(int sortOrder);
	void update();
	void render();
	void destroy();
	bool isDestroyed();
	void addChild(Entity* child);
	void setActive(bool isActive);
	bool isActive();
	int sortOrder = 0;
	Entity* parent = nullptr;

	template <typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		components.emplace_back(c);

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;

	}

	template<typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};