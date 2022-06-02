#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode({1280, 720}), "SFML");

	sf::Font font;
	if(!font.loadFromFile("arial.ttf"))
		return -1;

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(60);
	text.setString("hello world!");
	text.setOutlineColor(sf::Color::White);

	sf::Clock time;
	float value = 0.0;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
		}

		text.setOutlineThickness(value);
		value += 0.01;
		if (value > 10.0) {
			value = 0;
		}

		window.clear();
		window.draw(text);
		window.display();
		sf::sleep(sf::milliseconds(10));
	}
}
