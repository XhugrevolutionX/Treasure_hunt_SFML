// Treasure_hunt.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
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

	while (tries < tries_)
	{
		while (window.isOpen())
		{
			map.display_SFML(window);

			while(window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}

				victoire = map.dig(window,event,tries);

				if (tries >= tries_ && !victoire)
				{
					window.close();
					std::cout << "Bravo vous avez perdu\n";
				}
				if (victoire)
				{
					window.close();
					std::cout << "Bravo vous avez gagner\n";
				}
			}
		}
		map.display_SFML(window);
		std::cout << "Fin de partie\n";
		system("pause");

	}

}