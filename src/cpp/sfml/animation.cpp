#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({1080, 720}), "Image");
    window.setFramerateLimit(5);
    AssetManager manager;

    sf::Vector2i spriteSize({32, 32});
    sf::Sprite sprite(AssetManager::GetTexture("crystal-32-blue.png"));
    sprite.setTextureRect(sf::IntRect({0, 0}, {spriteSize.x, spriteSize.y}));

    sf::Vector2i boySpriteSize({104, 150});
    sf::Sprite boySprite(AssetManager::GetTexture("boy-sprite.png"));
    boySprite.setTextureRect(sf::IntRect({0, 0}, {boySpriteSize.x, boySpriteSize.y}));
    boySprite.move({100, 0});

    sf::Vector2i boy2SpriteSize({98, 237});
    sf::Sprite boy2(AssetManager::GetTexture("boy-sprite.png"));
    boy2.setTextureRect(sf::IntRect({0, 151}, {boy2SpriteSize.x, boy2SpriteSize.y}));
    boy2.move({200, 100});

    int32_t frameNum{8};
    float animationDuration {1.f};
    sf::Time elapsedTime;
    sf::Clock clock;

    sf::Texture texture;
    if(!texture.loadFromFile("crystal-32-blue.png")) {
        return -1;
    }
    texture.setSmooth(true);

    sf::RectangleShape rect({128, 128});
    rect.setOrigin({64, 64});
    rect.setTextureRect(sf::IntRect({0, 0}, {32, 32}));
    rect.setTexture(&texture);
    rect.move({1080/2, 720/2});

    while(window.isOpen()) {
        sf::Time deltaTime = clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            window.close();

        elapsedTime += deltaTime;
        float timeAsSeconds = elapsedTime.asSeconds();

        int32_t animFrame = static_cast<int32_t>((timeAsSeconds / animationDuration) * frameNum) % frameNum;
        sprite.setTextureRect(sf::IntRect({animFrame * spriteSize.x, 0}, {spriteSize.x, spriteSize.y}));
        rect.setTextureRect(sf::IntRect({animFrame * spriteSize.x, 0}, {spriteSize.x, spriteSize.y}));

        int32_t frame = static_cast<int32_t>((timeAsSeconds / animationDuration) * 6) % 6;
        boySprite.setTextureRect(sf::IntRect({frame * boySpriteSize.x, 0}, {boySpriteSize.x, boySpriteSize.y}));
        boySprite.move({4, 0});

        int32_t frame2 = static_cast<int32_t>((timeAsSeconds / animationDuration) * 7) % 7;
        boy2.setTextureRect(sf::IntRect({frame2 * boy2SpriteSize.x, 151}, {boy2SpriteSize.x, boy2SpriteSize.y}));

        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.draw(rect);
        window.draw(boySprite);
        window.draw(boy2);
        window.display();
    }
}