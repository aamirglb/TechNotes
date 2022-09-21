#include <SDL.h>
#include <iostream>
#include <string>

enum KeyPressSurface {
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL,
};

bool init();
bool loadMedia();
void close();
SDL_Surface* loadSurface(std::string path);


SDL_Window* win{};
SDL_Surface* screenSurface{};
SDL_Surface* keyPressedSurfaces[KeyPressSurface::KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* currentSurface{};

constexpr int32_t Width{ 640 };
constexpr int32_t Height{ 480 };



bool init() {
	bool success{ true };
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Unable to initialize: ";
		std::cerr << SDL_GetError() << std::endl;
		success = false;
	}
	else {
		win = SDL_CreateWindow("SDL Tutorial",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			Width,
			Height,
			SDL_WINDOW_SHOWN);

		if (!win) {
			std::cerr << "Window creation failed: ";
			std::cerr << SDL_GetError() << std::endl;
		}
		else {
			screenSurface = SDL_GetWindowSurface(win);
		}
	}
	return success;
}

SDL_Surface* loadSurface(std::string path) {
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (!loadedSurface) {
		std::cerr << "Unable to load image: " << path;
		std::cerr << " " << SDL_GetError() << std::endl;
	}
	return loadedSurface;
}

bool loadMedia() {
	bool success{ true };

	// default
	keyPressedSurfaces[KeyPressSurface::KEY_PRESS_SURFACE_DEFAULT] =
		loadSurface("../assets/press.bmp");
	if (!keyPressedSurfaces[KeyPressSurface::KEY_PRESS_SURFACE_DEFAULT]) {
		std::cerr << "Failed to load default image!\n";
		success = false;
	}

	// up
	keyPressedSurfaces[KeyPressSurface::KEY_PRESS_SURFACE_UP] =
		loadSurface("../assets/up.bmp");
	if (!keyPressedSurfaces[KeyPressSurface::KEY_PRESS_SURFACE_UP]) {
		std::cerr << "Failed to load up image!\n";
		success = false;
	}

	keyPressedSurfaces[KeyPressSurface::KEY_PRESS_SURFACE_DOWN] =
		loadSurface("../assets/down.bmp");
	if (!keyPressedSurfaces[KeyPressSurface::KEY_PRESS_SURFACE_DOWN]) {
		std::cerr << "Failed to load down image!\n";
		success = false;
	}

	keyPressedSurfaces[KeyPressSurface::KEY_PRESS_SURFACE_LEFT] =
		loadSurface("../assets/left.bmp");
	if (!keyPressedSurfaces[KeyPressSurface::KEY_PRESS_SURFACE_LEFT]) {
		std::cerr << "Failed to load left image!\n";
		success = false;
	}

	keyPressedSurfaces[KeyPressSurface::KEY_PRESS_SURFACE_RIGHT] =
		loadSurface("../assets/right.bmp");
	if (!keyPressedSurfaces[KeyPressSurface::KEY_PRESS_SURFACE_RIGHT]) {
		std::cerr << "Failed to load right image!\n";
		success = false;
	}

	return success;


	/*helloSurface = SDL_LoadBMP(img_name.c_str());
	if (!helloSurface) {
		std::cerr << "Unable to load image " << img_name << " ";
		std::cerr << SDL_GetError() << std::endl;
		success = false;
	}*/
	return success;
}

void close() {
	SDL_FreeSurface(currentSurface);
	currentSurface = nullptr;

	SDL_DestroyWindow(win);
	win = nullptr;

	SDL_Quit();
}

int main(int argc, char* argv[]) {
	if (!init()) {
		std::cerr << "Failed to initialize\n";
	}
	else {
		if (!loadMedia()) {
			std::cerr << "Failed to load media!\n";
		}
		else {
			SDL_Event e;
			bool quit{};
			currentSurface = keyPressedSurfaces[KEY_PRESS_SURFACE_DEFAULT];

			while (!quit) {
				while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN) {
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
							currentSurface = keyPressedSurfaces[KEY_PRESS_SURFACE_UP];
							break;
						case SDLK_DOWN:
							currentSurface = keyPressedSurfaces[KEY_PRESS_SURFACE_DOWN];
							break;
						case SDLK_LEFT:
							currentSurface = keyPressedSurfaces[KEY_PRESS_SURFACE_LEFT];
							break;
						case SDLK_RIGHT:
							currentSurface = keyPressedSurfaces[KEY_PRESS_SURFACE_RIGHT];
							break;
						case SDLK_ESCAPE:
							quit = true;
							break;
						default:
							currentSurface = keyPressedSurfaces[KEY_PRESS_SURFACE_DEFAULT];
							break;
						}
					}
				}
				SDL_BlitSurface(currentSurface, nullptr, screenSurface, nullptr);
				SDL_UpdateWindowSurface(win);
			}
		}
	}
	close();
	return 0;
}
