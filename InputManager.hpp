#pragma once
#include <SDL.h>
#include "Vector2.hpp"

class InputManager
{
public:
	static InputManager& Instance();
	InputManager(InputManager&) = delete;
	void handleInput(SDL_Event event);
	Vector2 getMousePos();
	bool getMouseDown();
	bool getMousePressed();
	bool getMouseReleased();

	void resetSingleFrameEvents();
	const int maxWheel = 0;
	const int minWheel = -2;
	bool buttonPressed = false;

private:
	InputManager();
	~InputManager();
	Vector2* mousePos;
	bool mouseDown = false;
	bool mousePressed = false;
	bool mouseReleased = false;
};