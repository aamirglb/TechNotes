
#include "game.h"
// our Game object
Game* g_game{};

int main(int argc, char* argv[])
{
	g_game = new Game();
	g_game->init("Chapter 1", 100, 100, 1080, 480, 0 /*SDL_WINDOW_BORDERLESS | SDL_WINDOW_FULLSCREEN*/);
	while(g_game->running()) {
		g_game->handleEvents();
		g_game->update();
		g_game->render();
	}

	g_game->clean();
	return 0;
}