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
	std::cout << Vector2(0, -1).angleBetween(Vector2(-1, 0));
	_gameRunning = true;
	FoodSpawner* foodSpawner = createFoodSpawner();
	spawnPreyFlock(15, Assets::Instance().triangleSprite, foodSpawner);
	spawnPreyFlock(15, Assets::Instance().triangleSpriteGreen, foodSpawner);
	spawnPreyFlock(15, Assets::Instance().triangleSpriteYellow, foodSpawner);
	spawnPredators(4);
	for (int i = 0; i < 4; i++)
		spawnBoundary();
	Entity& sliderBar = EntityManager::Instance().addEntity(3);
	sliderBar.addComponent<SpriteComponent>(Vector2(200, 200), 1, Assets::Instance().sliderSprite);
	Entity& slider = EntityManager::Instance().addEntity(4);
	slider.addComponent<SpriteComponent>(Vector2(200, 204), 1, Assets::Instance().knobSprite);
	slider.addComponent<PreyBoidSteeringSlider>("Seperation", 0, 1, .3, 200-8, 380-8, "Seperation");
}

void Game::update()
{
	while (_gameRunning)
	{
		Time::Instance().UpdateTime();
		handleEvents();
		EntityManager::Instance().refresh();
		EntityManager::Instance().update();
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

void Game::cleanUp()
{
	for (size_t i = 0; i < _flocks.size(); i++)
		delete _flocks[i];
	Assets::Instance().closeFonts();
	RenderWindow::Instance().cleanUp();
	SDL_Quit();
	TTF_Quit();
	IMG_Quit();
	delete this;
}

void Game::render()
{
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
		boid.addComponent<TransformComponent>(Vector2(utils::randomFloat(-RenderWindow::Instance().WIDTH / 2, RenderWindow::Instance().WIDTH / 2),
			utils::randomFloat(-RenderWindow::Instance().HEIGHT / 2, RenderWindow::Instance().HEIGHT / 2)), 0, Vector2(1, 1));
		boid.addComponent<WorldSpriteComponent>(tex);
		boid.addComponent<PreyBoidComponent>(3, .05, 19, 25, 90, flock, foodSpanwer);
	}
}

void Game::spawnPredators(int boids)
{
	for (int i = 0; i < boids; i++)
	{
		Entity& boid = EntityManager::Instance().addEntity(1);
		boid.addComponent<TransformComponent>(Vector2(utils::randomFloat(-RenderWindow::Instance().WIDTH / 2, RenderWindow::Instance().WIDTH / 2),
			utils::randomFloat(-RenderWindow::Instance().HEIGHT / 2, RenderWindow::Instance().HEIGHT / 2)), 0, Vector2(1, 1));
		boid.addComponent<WorldSpriteComponent>(Assets::Instance().predatorSprite);
		boid.addComponent<PredatorBoid>(2.5, .03, 40, 40, 90, &_predators);
	}
}

void Game::spawnBoundary()
{
	Entity& boundary = EntityManager::Instance().addEntity(2);
	TransformComponent* trans = &boundary.addComponent<TransformComponent>(Vector2(utils::randomFloat(-RenderWindow::Instance().WIDTH / 2, RenderWindow::Instance().WIDTH / 2),
		utils::randomFloat(-RenderWindow::Instance().HEIGHT / 2, RenderWindow::Instance().HEIGHT / 2)), 0, Vector2(1, 1));
	boundary.addComponent<WorldSpriteComponent>(Assets::Instance().boundarySprite);
	boundary.addComponent<BoundaryComponent>(25);
}

FoodSpawner* Game::createFoodSpawner()
{
	Entity& foodSpawner = EntityManager::Instance().addEntity(0);
	return &foodSpawner.addComponent<FoodSpawner>();
}