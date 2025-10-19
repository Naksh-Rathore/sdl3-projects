#include <iostream>
#include <array>

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>

int getKeyPress(bool& isRunning);
SDL_Window* getWindow();
std::array<int, 2> updateCords(int key, std::array<int, 2> cords);

int main(int argc, char* argv[]) {
	SDL_Window* window = getWindow();

	if (window == nullptr) {
		std::cerr << "Null pointer for window. Exiting..." << "\n";
		return EXIT_FAILURE;
	}

	bool isRunning = true;
	std::array<int, 2> cords = { 0, 0 };

	while (isRunning) {
		int key = getKeyPress(isRunning);

		/* w = 119
		   a = 97
	       s = 115
	       d = 100 */

		if (key == 119 || key == 97 || key == 115 || key == 100) {
			cords = updateCords(key, cords);

			std::cout << "New cords: " << "\n";
			std::cout << "X: " << cords[0] << "\n";
			std::cout << "Y: " << cords[1] << "\n\n";
		}
	}

	SDL_Quit();
}

int getKeyPress(bool &isRunning) {
	SDL_Event event;
	
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT) {
			isRunning = false;
			return 0;
		}

		else if (event.type == SDL_EVENT_KEY_DOWN) 
			return event.key.key;
		
		else
			return 0;
	}
}

SDL_Window* getWindow() {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		std::cerr << "Failed to initialize: " << SDL_GetError() << "\n";
		return nullptr;
	}

	SDL_Window* window = SDL_CreateWindow("SDL3", 800, 600, SDL_WINDOW_RESIZABLE);

	return window;
}

std::array<int, 2> updateCords(int key, std::array<int, 2> cords) {
	/* w = 119
	   a = 97
       s = 115
       d = 100 */

	switch (key) {
		case 119: cords[1] += 10; break;
		case 115: cords[1] -= 10; break;
		case 100: cords[0] += 10; break;
		case 97: cords[0] -= 10; break;
	}

	return cords;
}
