#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <string>
#include "SFML/Graphics.hpp"
#include "treasure_hunt_SFML.h"

int main()
{
	
	sf::RenderWindow window(sf::VideoMode(510, 510), "SFML treasure hunt!");
	sf::Event event;

	std::srand(std::time(nullptr));

	bool victoire;
	const int tries_ = 100;
	int tries = 0;
	Map map;

	map.initialize();
	map.place_treasure();
	map.display_SFML(window, tries);

	while (window.isOpen())
	{
		while(window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
			{
				window.close();
			}


			victoire = map.dig(window, event, tries);
			map.display_SFML(window, tries);


			if (tries >= tries_ && !victoire)
			{
				std::cout << "Bravo vous avez perdu\n";
				map.end(window, false);
			}
			if (victoire)
			{
				std::cout << "Bravo vous avez gagner\n";
				map.end(window, true);
			}
		}
	}
	std::cout << "Fin de partie\n";
}