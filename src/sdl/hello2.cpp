#include <SDL.h>
#include <iostream>

SDL_Window* window{};
SDL_Renderer* renderer{};
bool bRunning{};

bool init(const char* title, int xpos, int ypos, int height,
	int width, int flags) {
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
		window = SDL_CreateWindow(title,
			xpos,
			ypos,
			height,
			width,
			flags);
		if (window) {
			renderer = SDL_CreateRenderer(window, -1, 0);
		}
	}
	else {
		return false;
	}
	return true;
}

void render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
	
	if (init("SDL Hello",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_CENTERED,
		640,
		1080,
		SDL_WINDOW_SHOWN)) {
		bRunning = true;
	}
	else {
		return 1;
	}

	while (bRunning) {
		render();
	}

	//SDL_Event e;
	//bool quit{};
	//while (!quit) {
	//	while (SDL_PollEvent(&e)) {
	//		if (e.type == SDL_QUIT) {
	//			quit = true;
	//		}
	//		if (e.type == SDL_KEYDOWN) {
	//			if (e.key.keysym.sym == SDLK_ESCAPE) {
	//				quit = true;
	//			}
	//		}
	//	}
	//}

	//SDL_Delay(4000);
	SDL_Quit();
	return 0;
}
