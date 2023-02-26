#include <SDL.h>
#include <iostream>

// screen dimensions
constexpr int32_t Width {640};
constexpr int32_t Height {480};

int main(int argc, char* argv[]) {
    SDL_Window* window {};
    SDL_Surface* screenSurface {};
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    } else {
        window = SDL_CreateWindow("SDL Tutorial",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                Width,
                Height,
                SDL_WINDOW_SHOWN);
        if(!window) {
            std::cerr << "Window could not be created! SDL_ERROR: " << SDL_GetError() << std::endl;
        } else {
            screenSurface = SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0x0, 0xFF, 0xFF));
            SDL_UpdateWindowSurface(window);
            SDL_Event e;

            bool quit {};
            while(!quit) {
                while(SDL_PollEvent(&e)) {
                    if(e.type == SDL_QUIT) {
                        quit = true;
                    }
                }
            }
        }
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }


}
