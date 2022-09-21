#include "game_tile.h"

GameTile::GameTile(std::string textureName,
    float x, float y, bool passable, bool exit) {

    if(!setupSprite(textureName)) return;

    m_pos = sf::Vector2f(x, y);
    m_sprite.setPosition(pos);

    m_isPassable = passable;
    m_isExit = exit;
}

bool GameTile::setupSprite(std::string texName) {
    if(!m_texture.loadFromFile(texName)) {
        return false;
    }

    m_texture.setSmoorth(true);
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
    return true;
}