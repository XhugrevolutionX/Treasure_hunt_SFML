// Treasure_hunt.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include <array>
#include <algorithm>
#include <string>
#include "SFML/Graphics.hpp"
#include "treasure_hunt_SFML.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML treasure hunt!");
	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		std::srand(std::time(nullptr));

		bool victoire;
		const int tries_ = 10;

		Map map;

		map.initialize();
		map.place_treasure();

		for (int tries = 1; tries <= tries_; tries++)
		{
			map.display();
			victoire = map.dig();

			system("cls");
			if (tries >= tries_ && !victoire)
			{
				std::cout << "Bravo vous avez perdu\n";
			}
			else if (victoire)
			{
				std::cout << "Bravo vous avez gagner\n";
				tries = tries_;
			}


		}
		map.display();
		std::cout << "Fin de partie\n";
		system("pause");
	}

}