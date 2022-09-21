#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <windows.h>
using namespace sf;
using namespace std;
int stouch = 0;
int wtouch = 0;
int atouch = 0;
int dtouch = 0;
int gravity = 0;
int jump = 0;
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
void ycollision(sf::RectangleShape player, sf::RectangleShape objects[50], int objectsize)
{
    for (int i = 0; i < objectsize; i++)
    {
        sf::RectangleShape object = objects[i];

        float pydistance = (player.getPosition().y + player.getSize().y / 2) - (object.getPosition().y - object.getSize().y / 2);
        float nydistance = (player.getPosition().y - player.getSize().y / 2) - (object.getPosition().y + object.getSize().y / 2);
        float nxoedge = object.getPosition().x - object.getSize().x / 2;
        float pxoedge = object.getPosition().x + object.getSize().x / 2;
        if (player.getPosition().x > object.getPosition().x)
        {

            if (player.getPosition().x - player.getSize().x / 2 < pxoedge)
            {
                if (pydistance > 0.0f && pydistance < 0.11f)
                {

                    stouch = 1;
                    gravity = 1;
                    wtouch = 0;

                }
                if (nydistance < 0.0f && nydistance > -0.11f)
                {

                    wtouch = 1;
                    jump = 1;


                }
            }

        }
        if (player.getPosition().x < object.getPosition().x)
        {

            if (player.getPosition().x + player.getSize().x / 2 > nxoedge)
            {

                if (pydistance > 0.0f && pydistance < 0.11f)
                {
                    wtouch = 0;
                    stouch = 1;
                    gravity = 1;

                }
                if (nydistance < 0.0f && nydistance > -0.11f)
                {

                    wtouch = 1;
                    jump = 1;

                }
            }
        }


    }

};
void xcollision(sf::RectangleShape player, sf::RectangleShape objects[50], int objectsize)
{
    for (int i = 0; i < objectsize; i++)
    {
        sf::RectangleShape object = objects[i];
        float nyoedge = object.getPosition().y - object.getSize().y / 2;
        float pyoedge = object.getPosition().y + object.getSize().y / 2;

        float nypedge = player.getPosition().y - player.getSize().y / 2;
        float pypedge = player.getPosition().y + player.getSize().y / 2;
        float nxdistance = (player.getPosition().x + player.getSize().x / 2) - (object.getPosition().x - object.getSize().x / 2);
        float pxdistance = (player.getPosition().x - player.getSize().x / 2) - (object.getPosition().x + object.getSize().x / 2);
        if (player.getPosition().y < object.getPosition().y)
        {
            if (pypedge > nyoedge)
            {
                if (nxdistance < 0.0f && nxdistance > -0.11f)
                {
                    dtouch = 1;
                };
                if (pxdistance > 0.0f && pxdistance < 0.11f)
                {
                    atouch = 1;
                };
            };
        };
        if (player.getPosition().y > object.getPosition().y)
        {
            if (nypedge < pyoedge)
            {
                if (pxdistance > 0.0f && pxdistance < 0.11f)
                {
                    atouch = 1;
                };
                if (nxdistance < 0.0f && nxdistance > -0.11f)
                {
                    dtouch = 1;
                };
            };
        };
    };
};

int main()
{

    RenderWindow window(VideoMode({800, 900}), "Collision Chaos!");
    RectangleShape player(Vector2f(50.0f, 50.0f));
    Event event;
    Rect<float> playersize = player.getGlobalBounds();
    player.setOrigin(Vector2f(playersize.width / 2,playersize.height / 2));
    player.setFillColor(Color::Red);
    RectangleShape objects[50];
    RectangleShape object(Vector2f(300.0f, 60.0f));
    Rect<float> objectsize = object.getGlobalBounds();
    object.setOrigin(Vector2f(objectsize.width / 2, objectsize.height / 2));
    object.setPosition(Vector2f(200.0f, 200.0f));
    objects[0] = object;
    RectangleShape object2(Vector2f(200.0f, 50.0f));
    Rect<float> objectsize2 = object2.getGlobalBounds();
    object2.setOrigin(Vector2f(objectsize2.width / 2, objectsize2.height / 2));
    object2.setPosition(Vector2f(100.0f, 320.0f));
    objects[1] = object2;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

        }


        xcollision(player, objects, 2);
        ycollision(player, objects, 2);
        if (gravity == 0)
        {
            player.setPosition({player.getPosition().x, player.getPosition().y + 0.05f});
        };

        std::cout << jump;
        if (jump == 0)
        {
            if (Keyboard::isKeyPressed(Keyboard::W))
            {
                if (wtouch == 0 && jump == 0)
                {
                    for (int i = 0; i < 50; i++)
                    {

                        if (jump == 0)
                        {
                            float jumpheight = 1.0f;
                            player.setPosition({player.getPosition().x, player.getPosition().y - jumpheight});

                        }
                        if (jump == 1)
                        {
                            i = 999;

                        };
                    };
                };
            };
        };
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            if (atouch == 0)
            {
            player.setPosition({player.getPosition().x - 0.05f, player.getPosition().y});
            };

        };
        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            if (dtouch == 0)
            {
            player.setPosition({player.getPosition().x + 0.05f, player.getPosition().y});
            };
        };
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            if (stouch == 0)
            {

            player.setPosition({player.getPosition().x, player.getPosition().y + 0.05f});

            };

        };

            window.clear();
            stouch = 0;
            wtouch = 1;
            atouch = 0;
            dtouch = 0;
            gravity = 0;
            jump = 0;

                    window.draw(player);
                window.draw(object);
                window.draw(object2);
                window.display();
    };
   return 0;
    }