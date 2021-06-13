#include "Game.h"
// our Game object
Game* g_game = 0;
int main(int argc, char* argv[])
{
g_game = new Game();
g_game->init("Chapter 1", 100, 100, 640, 480, 0);
while(g_game->running())
{
g_game->handleEvents();
g_game->update();
g_game->render();
}
g_game->clean();
return 0;
}