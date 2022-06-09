#pragma once

#include <SFML/Graphics.hpp>
#include <map>

class AssetManager
{
public:
    AssetManager();
    static sf::Texture& GetTexture(const std::string &filename);

private:
    std::map<std::string, sf::Texture> _textures;
    static AssetManager* sInstance;
};