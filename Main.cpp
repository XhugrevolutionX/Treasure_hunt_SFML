#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <string>
#include "treasure_hunt_SFML.h"

int main()
{
	
	sf::RenderWindow window(sf::VideoMode(510, 510), "SFML treasure hunt!");
	sf::Event event;
	std::array<sf::RectangleShape, map_size> arr;

	std::srand(std::time(nullptr));

	bool victoire = false;
	const int tries_ = 100;
	int tries = 0;

	float dt = 0.0f;
	float counter = 0;
	sf::Clock clock;

	sf::Font font;
	if (!font.loadFromFile("Assets\\BrownieStencil.ttf"))
	{

	}

	sf::Text shutdown_text;
	shutdown_text.setFont(font);
	shutdown_text.setPosition(75, 250);
	shutdown_text.setCharacterSize(25);
	shutdown_text.setFillColor(sf::Color::Red);

	



	Map map;

	map.initialize();
	map.place_treasure();

	while (window.isOpen())
	{

		while(window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.mouseButton.button == sf::Mouse::Button::Left && event.type == sf::Event::MouseButtonReleased)
			{
				if (!victoire)
				{
					victoire = map.dig(tries, event.mouseButton.x, event.mouseButton.y);
				}
			}
			map.SFML_actualize(window, arr);
		}

		window.clear();
		map.display_SFML(window, tries, arr);

		if (victoire)
		{
			counter += dt;
			int count_down = 5 - counter;
			std::string str = "The Game will shut down in ";

			str.append(std::to_string(count_down));
			shutdown_text.setString(str);

			window.draw(shutdown_text); // doesn't draw (why?????????????)
			if (counter > 5)
				window.close();
		}

		dt = clock.restart().asSeconds();

		if (tries >= tries_ && !victoire)
		{
			map.end(window, false);
		}
		if (victoire)
		{
			map.end(window, true);
		}


		window.display();
	}
	std::cout << "Fin de partie\n";
}