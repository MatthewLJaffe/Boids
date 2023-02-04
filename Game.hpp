#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "EntityManager.hpp"
#include "Time.hpp"
#include "RenderWindow.hpp"
#include "Assets.hpp"
#include "SpriteComponent.hpp"
#include "WorldSpriteComponent.hpp"
#include "PredatorBoid.hpp"
#include "PreyBoidComponent.hpp"
#include "FoodSpawner.hpp"
#include "BoundaryComponent.hpp"
#include "InputManager.hpp"
#include "PreyBoidSteeringSlider.hpp"

class FoodSpawner;

class Game
{
public:
	Game();
	void init();
	void update();
	void cleanUp();

private:
	void handleEvents();
	void render();
	void spawnPreyFlock(int boids, SDL_Texture* tex, FoodSpawner* spawner);
	void spawnPredators(int boids);
	void spawnBoundary();
	FoodSpawner* createFoodSpawner();
	bool _gameRunning = false;
	std::vector<std::vector<BoidComponent*>*> _flocks;
	std::vector<BoidComponent*> _predators;
};

