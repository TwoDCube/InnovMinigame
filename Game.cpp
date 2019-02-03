#include "Game.h"
#include "LED.h"

LED *led;
std::vector<bool> allled;
int selectedled = NULL;
int gamestate = 0;
bool win = false;
int tick = 0;

Game::Game()
= default;

Game::~Game()
= default;

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;
	
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

        led = new LED;
		led->init();

		for (int i = 0; i < 8; i++) {
			allled.push_back(false);
		}

		isRunning = true;
	}
}

void Game::handleEvents()
{
	SDL_Event event;

	SDL_PollEvent(&event);
	SDL_KeyboardEvent thisevent;

	switch (event.type)
	{
		case SDL_KEYDOWN:
			thisevent = event.key;
			if (thisevent.keysym.sym == SDLK_a) {
				button1 = true;
			}
			if (thisevent.keysym.sym == SDLK_d) {
				button2 = true;
			}
			break;

		case SDL_KEYUP:
			thisevent = event.key;
			if (thisevent.keysym.sym == SDLK_a) {
				button1 = false;
			}
			if (thisevent.keysym.sym == SDLK_d) {
				button2 = false;
			}
			break;

		case SDL_QUIT :
			isRunning = false;
			break;

		default:
			break;
	}
}

void Game::update()
{
    tick++;
	srand (time(NULL));
 	switch (gamestate) {
 		case 0: // We need to start a new led

 			// Select a randpom led turn it red and make its value false
 			selectedled = rand() % 8;
 			led->change(selectedled, 255, 0, 0, 255);
 			gamestate = 1; // waiting for user input
			break;

 		case 1: // waiting for user input
            if (tick % 120 == 0) {
                if(allled.at(selectedled)){
                    led->change(selectedled, 0, 255, 0, 255);
                } else {
                    led->change(selectedled, 0, 0, 0, 0);
                }
            }
            if (tick % 120 == 60) {
                led->change(selectedled, 255, 0, 0, 255);
            }
 			if(isButton1Pressed()) {
 				if (selectedled != 0) {
 					if (allled.at(selectedled-1)) {
						led->change(selectedled-1, 0, 0, 0, 0);
						allled.at(selectedled-1) = false;
 					} else {
						led->change(selectedled-1, 0, 255, 0, 255);
						allled.at(selectedled-1) = true;
 					}

 				}
 				if (selectedled != 7) {
					if (allled.at(selectedled+1)) {
						led->change(selectedled+1, 0, 0, 0, 0);
						allled.at(selectedled+1) = false;
					} else {
						led->change(selectedled+1, 0, 255, 0, 255);
						allled.at(selectedled+1) = true;
					}
 				}

 				// Turn off red led
 				if (allled.at(selectedled)) {
 					led->change(selectedled, 0, 255, 0, 255);
 				} else {
 					led->change(selectedled, 0, 0, 0, 0);
 				}

 				// Check if we won
 				win = true;
 				for (bool led : allled) {
 					if (!led) win = false;
 				}
 				if (win) std::cout << "WIN" << std::endl;

 				SDL_Delay(250);
 				gamestate = 0;
 			} else if (isButton2Pressed()) {
				if (allled.at(selectedled)) {
					led->change(selectedled, 0, 0, 0, 0);
					allled.at(selectedled) = false;
				} else {
					led->change(selectedled, 0, 255, 0, 255);
					allled.at(selectedled) = true;
				}

				// Check if we won
				win = true;
				for (bool led : allled) {
					if (!led) win = false;
				}
				if (win) std::cout << "WIN" << std::endl;

				SDL_Delay(250);
				gamestate = 0;
 			}
			break;


 	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	led->render(renderer);
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}