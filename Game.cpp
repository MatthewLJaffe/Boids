#include "Game.hpp"

Game::Game() {}

void Game::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
		std::cout << "SDL_Init HAS FAILED. ADL_ERROR: " << SDL_GetError() << std::endl;
	if (!IMG_Init(IMG_INIT_PNG))
		std::cout << "IMG_Init has failed" << SDL_GetError() << std::endl;
	if (TTF_Init() > 0)
		std::cout << "TTF_Init has failed" << SDL_GetError() << std::endl;
	Assets::Instance().loadAssets();
	_gameRunning = true;
	buildGame();
}

void Game::buildGame()
{
	FoodSpawner* foodSpawner = createFoodSpawner();
	spawnPreyFlock(60, Assets::Instance().triangleSprite, foodSpawner);
	spawnPreyFlock(60, Assets::Instance().triangleSpriteGreen, foodSpawner);
	spawnPreyFlock(60, Assets::Instance().triangleSpriteYellow, foodSpawner);
	createWorldBoundary();
	spawnPredators(12);
	for (int i = 0; i < 20; i++)
		spawnBoundary();
	buildUI(foodSpawner);
}

void Game::update()
{
	while (_gameRunning)
	{
		Time::Instance().UpdateTime();
		handleEvents();
		EntityManager::Instance().refresh();
		EntityManager::Instance().update();
		handleDragInput();
		render();
		InputManager::Instance().resetSingleFrameEvents();
	}
}

void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		InputManager::Instance().handleInput(event);
		if (event.type == SDL_QUIT)
			_gameRunning = false;
	}
}

void Game::handleDragInput()
{
	if (!InputManager::Instance().getMouseDown() || InputManager::Instance().buttonPressed) return;
	if (InputManager::Instance().getMousePressed())
	{
		_lastMousePos = InputManager::Instance().getMousePos();
		return;
	}
	WorldSpriteComponent::worldOffset += InputManager::Instance().getMousePos() - _lastMousePos;
	if (WorldSpriteComponent::worldOffset.x < -utils::roundFloat(maxPos.x - RenderWindow::WIDTH / 2) - boundaryRadius / 2)
		WorldSpriteComponent::worldOffset.x = -utils::roundFloat(maxPos.x - RenderWindow::WIDTH / 2) - boundaryRadius / 2;
	if (WorldSpriteComponent::worldOffset.x > utils::roundFloat(-minPos.x - RenderWindow::WIDTH / 2) + boundaryRadius / 2)
		WorldSpriteComponent::worldOffset.x = utils::roundFloat(-minPos.x - RenderWindow::WIDTH / 2) + boundaryRadius / 2;

	if (WorldSpriteComponent::worldOffset.y < -utils::roundFloat(maxPos.y - RenderWindow::HEIGHT / 2) - boundaryRadius / 2)
		WorldSpriteComponent::worldOffset.y = -utils::roundFloat(maxPos.y - RenderWindow::HEIGHT / 2) - boundaryRadius / 2;
	if (WorldSpriteComponent::worldOffset.y > utils::roundFloat(-minPos.y - RenderWindow::HEIGHT / 2) + boundaryRadius / 2)
		WorldSpriteComponent::worldOffset.y = utils::roundFloat(-minPos.y - RenderWindow::HEIGHT / 2) + boundaryRadius / 2;
	_lastMousePos = InputManager::Instance().getMousePos();
}

void Game::render()
{
	//dont render before update has been called on all entities
	if (_gameReset)
	{
		_gameReset = false;
		return;
	}
	RenderWindow::Instance().clear();
	EntityManager::Instance().render();
	RenderWindow::Instance().display();
}

void Game::spawnPreyFlock(int boids, SDL_Texture* tex, FoodSpawner* foodSpanwer)
{
	std::vector<BoidComponent*>* flock = new std::vector<BoidComponent*>();
	_flocks.push_back(flock);
	for (int i = 0; i < boids; i++)
	{
		Entity& boid = EntityManager::Instance().addEntity(0);
		boid.addComponent<TransformComponent>(Vector2(utils::randomFloat(minPos.x, maxPos.x),
			utils::randomFloat(minPos.y, maxPos.y)), 0, Vector2(1, 1));
		boid.addComponent<WorldSpriteComponent>(tex);
		boid.addComponent<PreyBoidComponent>(3.0f, .05f, 19.0f, 25.0f, 90.0f, 250.0f, flock, foodSpanwer);
	}
}

void Game::createWorldBoundary()
{
	//top
	for (float x = minPos.x - boundaryRadius/2; x <= maxPos.x + boundaryRadius/2; x += boundaryRadius)
	{
		spawnBoundary(x, minPos.y - boundaryRadius / 2);
	}
	//bottom
	for (float x = minPos.x - boundaryRadius / 2; x <= maxPos.x + boundaryRadius / 2; x += boundaryRadius)
	{
		spawnBoundary(x, maxPos.y + boundaryRadius / 2);
	}
	//left
	for (float y = minPos.y + boundaryRadius / 2; y <= maxPos.y - boundaryRadius / 2; y += boundaryRadius)
	{
		spawnBoundary(minPos.x - boundaryRadius / 2, y);
	}
	//right
	for (float y = minPos.y + boundaryRadius / 2; y <= maxPos.y - boundaryRadius / 2; y += boundaryRadius)
	{
		spawnBoundary(maxPos.x + boundaryRadius / 2, y);
	}
}

void Game::spawnPredators(int boids)
{
	for (int i = 0; i < boids; i++)
	{
		Entity& boid = EntityManager::Instance().addEntity(1);
		boid.addComponent<TransformComponent>(Vector2(utils::randomFloat(minPos.x, maxPos.x),
			utils::randomFloat(minPos.y, maxPos.y)), 0, Vector2(1, 1));
		boid.addComponent<WorldSpriteComponent>(Assets::Instance().predatorSprite);
		boid.addComponent<PredatorBoid>(2.5f, .03f, 40.0f, 40.0f, 90.0f, 200.0f, &_predators);
	}
}

void Game::spawnBoundary()
{
	Entity& boundary = EntityManager::Instance().addEntity(2);
	boundary.addComponent<TransformComponent>(Vector2(utils::randomFloat(minPos.x, maxPos.x),
		utils::randomFloat(minPos.y, maxPos.y)), 0, Vector2(1, 1));
	boundary.addComponent<WorldSpriteComponent>(Assets::Instance().boundarySprite);
	boundary.addComponent<BoundaryComponent>(25.0f);
}

void Game::spawnBoundary(float x, float y)
{
	Entity& boundary = EntityManager::Instance().addEntity(2);
	boundary.addComponent<TransformComponent>(Vector2(x, y), 0, Vector2(1, 1));
	boundary.addComponent<WorldSpriteComponent>(Assets::Instance().boundarySprite);
	boundary.addComponent<BoundaryComponent>(25.0f);
}

FoodSpawner* Game::createFoodSpawner()
{
	Entity& foodSpawner = EntityManager::Instance().addEntity(0);
	return &foodSpawner.addComponent<FoodSpawner>(minPos, maxPos);
}

void Game::buildUI(FoodSpawner* foodSpawner)
{
	SDL_Color black = { 0, 0, 0 };
	Vector2 quitButtonPos = Vector2(50, 50);
	Entity& quitButton = EntityManager::Instance().addEntity(4);
	quitButton.addComponent<SpriteComponent>(quitButtonPos, 1.0f, Assets::Instance().buttonUp);
	quitButton.addComponent<TextComponent>("Quit", quitButtonPos + Vector2(32, 12), 1.0f, 24, Assets::Instance().font, black, false);
	auto quitGame = [this]() {_gameRunning = false; };
	quitButton.addComponent<ButtonComponent>(Assets::Instance().buttonUp, Assets::Instance().buttonDown, quitGame);

	Vector2 resetButtonPos = Vector2(200, 50);
	Entity& resetButton = EntityManager::Instance().addEntity(4);
	resetButton.addComponent<SpriteComponent>(resetButtonPos, 1.0f, Assets::Instance().buttonUp);
	resetButton.addComponent<TextComponent>("Reset", resetButtonPos + Vector2(28, 12), 1.0f, 24, Assets::Instance().font, black, false);
	auto reset = [this]() {resetGame(); };
	resetButton.addComponent<ButtonComponent>(Assets::Instance().buttonUp, Assets::Instance().buttonDown, reset);

	Entity& preyStatsEntity = EntityManager::Instance().addEntity(4);
	SDL_Color white = { 255, 255, 255 };
	float sliderSpace = 30;
	Vector2 preyStatsPos = Vector2(RenderWindow::WIDTH - 450.0f, 40.0f);
	preyStatsEntity.addComponent<TextComponent>("Prey", preyStatsPos, 1.0f, 24, Assets::Instance().font, white, false);
	preyStatsEntity.addComponent<SpriteComponent>(preyStatsPos + Vector2(-30, 12), 1.0f, Assets::Instance().arrowDown);
	std::vector<SliderComponent*> preySliders;
	preyStatsPos.y += 10;
	addSlider(Vector2(RenderWindow::WIDTH - 300.0f, preyStatsPos.y + sliderSpace * 1.0f), "Seperation", "Seperation", .4f, 0, 1, preySliders, "Prey");
	addSlider(Vector2(RenderWindow::WIDTH - 300.0f, preyStatsPos.y + sliderSpace * 2.0f), "Alignment", "Alignment", .3f, 0, 1, preySliders, "Prey");
	addSlider(Vector2(RenderWindow::WIDTH - 300.0f, preyStatsPos.y + sliderSpace * 3.0f), "Cohesion", "Cohesion", .3f, 0, 1, preySliders, "Prey");
	addSlider(Vector2(RenderWindow::WIDTH - 300.0f, preyStatsPos.y + sliderSpace * 4.0f), "Speed", "Speed", 2.5, 0, 5, preySliders, "Prey");
	addSlider(Vector2(RenderWindow::WIDTH - 300.0f, preyStatsPos.y + sliderSpace * 5.0f), "Acceleration", "Acceleration", 6, 0, 10, preySliders, "Prey");
	addSlider(Vector2(RenderWindow::WIDTH - 300.0f, preyStatsPos.y + sliderSpace * 6.0f), "Food Attraction", "Food Attraction", .5, 0, 1, preySliders, "Prey");
	addSlider(Vector2(RenderWindow::WIDTH - 300.0f, preyStatsPos.y + sliderSpace * 7.0f), "Predator Avoidance", "AvoidPredators", .75, 0, 1, preySliders, "Prey");
	addSlider(Vector2(RenderWindow::WIDTH - 300.0f, preyStatsPos.y + sliderSpace * 8.0f), "Field of View", "Field of View", 360, 0, 360, preySliders, "Prey");
	addSlider(Vector2(RenderWindow::WIDTH - 300.0f, preyStatsPos.y + sliderSpace * 9.0f), "Vision Radius", "Vision Radius", 250, 0, 500, preySliders, "Prey");
	StatBlock* preyBlock = &preyStatsEntity.addComponent<StatBlock>(preySliders, true);

	Entity& predatorStatsEntity = EntityManager::Instance().addEntity(4);
	Vector2 predatorStatsPos = Vector2(RenderWindow::WIDTH - 450.0f, 90.0f);
	predatorStatsEntity.addComponent<TextComponent>("Predator", predatorStatsPos, 1.0f, 24, Assets::Instance().font, white, false);
	predatorStatsEntity.addComponent<SpriteComponent>(predatorStatsPos + Vector2(-30, 12), 1.0f, Assets::Instance().arrowDown);
	std::vector<SliderComponent*> predatorSliders;
	predatorStatsPos.y += 10;
	addSlider(Vector2(RenderWindow::WIDTH - 300.0f, predatorStatsPos.y + sliderSpace * 1.0f), "Aggression", "Aggression", .7f, 0, 1, predatorSliders, "Predator");
	addSlider(Vector2(RenderWindow::WIDTH - 300.0f, predatorStatsPos.y + sliderSpace * 2.0f), "Speed", "Speed", 2.6f, 0, 5, predatorSliders, "Predator");
	addSlider(Vector2(RenderWindow::WIDTH - 300.0f, predatorStatsPos.y + sliderSpace * 3.0f), "Acceleration", "Acceleration", 4, 0, 10, predatorSliders, "Predator");
	addSlider(Vector2(RenderWindow::WIDTH - 300.0f, predatorStatsPos.y + sliderSpace * 4.0f), "Starvation Time", "Starvation Time", 30, 0, 60, predatorSliders, "Predator");
	addSlider(Vector2(RenderWindow::WIDTH - 300.0f, predatorStatsPos.y + sliderSpace * 5.0f), "Food to Reproduce", "Food to Reproduce", 4, 1, 10, predatorSliders, "Predator");
	addSlider(Vector2(RenderWindow::WIDTH - 300.0f, predatorStatsPos.y + sliderSpace * 6.0f), "Field of View", "Field of View", 180, 0, 360, predatorSliders, "Predator");
	addSlider(Vector2(RenderWindow::WIDTH - 300.0f, predatorStatsPos.y + sliderSpace * 7.0f), "Vision Radius", "Vision Radius", 200, 0, 500, predatorSliders, "Predator");
	predatorStatsEntity.addComponent<StatBlock>(predatorSliders, false);


	Entity& foodStatsEntity = EntityManager::Instance().addEntity(4);
	Vector2 foodStatsPos = Vector2(RenderWindow::WIDTH - 450.0f, 140.0f);
	foodStatsEntity.addComponent<TextComponent>("Prey Food", foodStatsPos, 1.0f, 24, Assets::Instance().font, white, false);
	foodStatsEntity.addComponent<SpriteComponent>(foodStatsPos + Vector2(-30, 12), 1.0f, Assets::Instance().arrowDown);
	std::vector<SliderComponent*> foodSliders;
	foodStatsPos.y += 10;
	addSlider(Vector2(RenderWindow::WIDTH - 300.0f, foodStatsPos.y + sliderSpace * 1.0f), "Spawn Rate", "Spawn Rate", .3f, 0, 1, foodSliders, "Food");
	addSlider(Vector2(RenderWindow::WIDTH - 300.0f, foodStatsPos.y + sliderSpace * 2.0f), "Food to Reproduce", "Food to Reproduce", 2, 1, 3, foodSliders, "Food");
	for (auto slider : foodSliders)
	{
		dynamic_cast<FoodSlider*>(slider)->setFoodSpawner(foodSpawner);
	}
	foodStatsEntity.addComponent<StatBlock>(foodSliders, false);
	preyBlock->toggleBlockVisibility();
}

void Game::addSlider(Vector2 pos, std::string name, std::string param, float value, float minValue, float maxValue, std::vector<SliderComponent*>& sliders, std::string sliderType)
{
	float sliderWidth = 180;
	float leftPadding = 30;
	float rightPadding = 30;
	float knobRadius = 8;
	int fontSize = 16;

	Entity& sliderKnob = EntityManager::Instance().addEntity(4);
	SpriteComponent* knobSprite = &sliderKnob.addComponent<SpriteComponent>(Vector2(pos.x - knobRadius, pos.y + knobRadius/2), 1.0f, Assets::Instance().knobSprite);

	Entity& sliderName = EntityManager::Instance().addEntity(3);
	SDL_Color color = { 255, 255, 255 };
	TextComponent* nameText = &sliderName.addComponent<TextComponent>(name, Vector2(pos.x - leftPadding, pos.y), 1.0f, fontSize, Assets::Instance().font, color, true);

	Entity& sliderAmount = EntityManager::Instance().addEntity(3);
	TextComponent* amountText = &sliderAmount.addComponent<TextComponent>("1", Vector2(pos.x + sliderWidth + rightPadding, pos.y), 1.0f, fontSize, Assets::Instance().font, color, false);

	Entity& slider = EntityManager::Instance().addEntity(3);
	slider.addComponent<SpriteComponent>(Vector2(pos.x, pos.y), 1.0f, Assets::Instance().sliderSprite);
	slider.addChild(&sliderKnob);
	slider.addChild(&sliderName);
	slider.addChild(&sliderAmount);
	if (sliderType == "Prey")
	{
		PreyBoidSlider* sliderComp = &slider.addComponent<PreyBoidSlider>(name, minValue, maxValue, value, pos.x - knobRadius, pos.x + sliderWidth - knobRadius, nameText, amountText, knobSprite, param);
		sliders.push_back(sliderComp);
	}
	else if (sliderType == "Predator")
	{
		if (param == "Food to Reproduce")
		{
			PredatorSlider* sliderComp = &slider.addComponent<PredatorSlider>(name, minValue, maxValue, value, pos.x - knobRadius, pos.x + sliderWidth - knobRadius, nameText, amountText, knobSprite, param, true);
			sliders.push_back(sliderComp);
		}
		else
		{
			PredatorSlider* sliderComp = &slider.addComponent<PredatorSlider>(name, minValue, maxValue, value, pos.x - knobRadius, pos.x + sliderWidth - knobRadius, nameText, amountText, knobSprite, param, false);
			sliders.push_back(sliderComp);
		}
	}
	else
	{
		if (param == "Food to Reproduce")
		{
			FoodSlider* sliderComp = &slider.addComponent<FoodSlider>(name, minValue, maxValue, value, pos.x - knobRadius, pos.x + sliderWidth - knobRadius, nameText, amountText, knobSprite, param, true);
			sliders.push_back(sliderComp);
		}
		else
		{
			FoodSlider* sliderComp = &slider.addComponent<FoodSlider>(name, minValue, maxValue, value, pos.x - knobRadius, pos.x + sliderWidth - knobRadius, nameText, amountText, knobSprite, param, false);
			sliders.push_back(sliderComp);
		}
	}
}

void Game::resetGame()
{
	StatBlock::statBlocks.clear();
	BoidComponent::allBoids.clear();
	PreyBoidComponent::preyBoids.clear();
	PredatorBoid::predatorBoids.clear();
	BoundaryComponent::boundaries.clear();
	EntityManager::Instance().clearEntities();
	buildGame();
	_gameReset = true;
}

void Game::cleanUp()
{
	for (size_t i = 0; i < _flocks.size(); i++)
		delete _flocks[i];
	EntityManager::Instance().clearEntities();
	Assets::Instance().closeFonts();
	RenderWindow::Instance().cleanUp();
	SDL_Quit();
	TTF_Quit();
	IMG_Quit();
	delete this;
}