#include "AssetManager.hpp"
#include <assert.h>
#include <exception>

AssetManager* AssetManager::sInstance = nullptr;

AssetManager::AssetManager()
{
    assert(sInstance == nullptr);
    sInstance = this;
}

sf::Texture& AssetManager::GetTexture(const std::string &filename)
{
    if(sInstance == nullptr)
        throw "AssetManager instance not defined";

    auto& texMap = sInstance->_textures;

    auto itr = texMap.find(filename);
    if(itr != texMap.end()) {
        return itr->second;
    } else {
        auto& texture = texMap[filename];
        if(texture.loadFromFile(filename)) {
            return texture;
        } else {
            std::string msg = filename + " not found.";
            throw std::invalid_argument(msg);
        }
    }
}