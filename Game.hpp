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
#include "PreyBoidSlider.hpp"
#include "PredatorSlider.hpp"
#include "FoodSlider.hpp"
#include "StatBlock.hpp"
#include "ButtonComponent.hpp"

class FoodSpawner;

class Game
{
public:
	Game();
	void init();
	void update();
	void cleanUp();
	const float boundaryRadius = 50;
private:
	void resetGame();
	void buildGame();
	void handleEvents();
	void render();
	void spawnPreyFlock(int boids, SDL_Texture* tex, FoodSpawner* spawner);
	void spawnPredators(int boids);
	void spawnBoundary();
	void spawnBoundary(float x, float y);
	void handleDragInput();
	bool _gameReset = false;
	void createWorldBoundary();
	void buildUI(FoodSpawner* foodSpawner);
	void addSlider(Vector2 pos, std::string name, std::string param, float value, float minValue, float maxValue, std::vector<SliderComponent*>& sliders, std::string sliderType);
	FoodSpawner* createFoodSpawner();
	bool _gameRunning = false;
	std::vector<std::vector<BoidComponent*>*> _flocks;
	std::vector<BoidComponent*> _predators;
	Vector2 _lastMousePos = Vector2(0, 0);
	Vector2 minPos = Vector2(-2000, -1500);
	Vector2 maxPos = Vector2(2000, 1500);
};

