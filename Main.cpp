#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <string>
#include "treasure_hunt_SFML.h"

int main()
{
	
	sf::RenderWindow window(sf::VideoMode(830, 830), "SFML treasure hunt!");
	sf::Event event;
	std::array<sf::Sprite, map_size> arr;

	std::srand(std::time(nullptr));

	bool victoire = false;
	const int max_tries = 15;
	int tries = 0;

	float dt = 0.0f;
	float counter = 0;
	sf::Clock clock;

	sf::Font font;
	if (!font.loadFromFile("Assets\\BrownieStencil.ttf"))
	{

	}

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
				if (!victoire && tries < max_tries)
				{
					victoire = map.dig(tries, event.mouseButton.x, event.mouseButton.y);
				}
			}
			map.SFML_actualize(window, arr);
		}

		window.clear();
		map.display_SFML(window, tries, arr);

		if (tries >= max_tries && !victoire)
		{
			map.end(window, false, counter, dt);
		}
		if (victoire)
		{
			map.end(window, true, counter, dt);
		}

		if (counter > 5)
		{
			window.close();
		}


		dt = clock.restart().asSeconds();

		window.display();
	}
	std::cout << "Fin de partie\n";

}