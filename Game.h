#pragma once

#include <SDL2/SDL.h>
#include <iostream>

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	bool isButton1Pressed() { return button1; }
	bool isButton2Pressed() { return button2; }
	void render();
	void clean();

private:
    bool button1 = false;
    bool button2 = false;
	bool isRunning = false;
	SDL_Window *window;
	SDL_Renderer *renderer;
};