#include "game-world.h"

GameWorld::GameWorld() {
    m_gridLength = 8;
    setupInitialState();
}

void GameWorld::setupInitialState() {
    m_exitPos = sf::Vector2i(1, 0);
    m_playerPos = sf::Vector2i(m_girdLength - 1, m_girdLength - 1);
    setupEnemyPosition();
    setupTiles();
}

void GameWorld::setupEnemyPosition() {
    m_enemyPos.clear();
    m_enemyPos.push_back(sf::Vector2i(0, 2));
    m_enemyPos.push_back(sf::Vector2i(6, 2));
    m_enemyPos.push_back(sf::Vector2i(2, 7));
}

void GameWorld::setupTiles() {
    m_tiles.clear();
    std::vector<GameTile *> row;
    row.push_back(new GameTile("images/wall.png", 0, 0, false, false));
    row.push_back(new GameTile("images/door.png", 50, 0, true, true));
    row.push_back(new GameTile("images/wall.png", 100, 0, false, false));
    row.push_back(new GameTile("images/wall.png", 150, 0, false, false));
    row.push_back(new GameTile("images/wall.png", 200, 0, false, false));
    row.push_back(new GameTile("images/wall.png", 250, 0, false, false));
    row.push_back(new GameTile("images/enemy.png", 300, 0, true, false));
    row.push_back(new GameTile("images/wall.png", 350, 0, false, false));
    m_tiles.push_back(row);
}
